/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <memory>
#include "../Client/AClient.hpp"
#include "TCPBoostSocket.hpp"

RType::Network::Socket::TCPBoostSocket::TCPBoostSocket(
    boost::asio::io_service& service,
    const std::shared_ptr<Common::Log::Log>& log,
    const std::shared_ptr<std::condition_variable>& cv) {
    this->_socket = std::make_shared<boost_socket_tcp_t>(service);
    this->_logger = log;
    this->_socket_error_notifier = cv;
}

void RType::Network::Socket::TCPBoostSocket::shutdown_socket() noexcept {
    this->_is_functional = false;
    if (this->_socket->is_open()) {
        boost::system::error_code ec;
        this->_socket->shutdown(
            boost::asio::socket_base::shutdown_type::shutdown_both, ec);
        if (ec)
            this->_logger->Error("[socket-> (tcp)] Shutdown: ", ec.message());
        this->_socket->cancel(ec);
        if (ec)
            this->_logger->Error("[socket-> (tcp)] Cancel: ", ec.message());
        this->_socket->close(ec);
        if (ec)
            this->_logger->Error("[socket-> (tcp)] Close: ", ec.message());
        this->_logger->Debug(this, " socket (tcp) successfully closed");
    } else
        this->_logger->Debug(this, " socket (tcp) already closed");
}

void RType::Network::Socket::TCPBoostSocket::read() {
    std::shared_ptr<MessageArr_t> raw_message = std::make_shared<MessageArr_t>();

    this->_logger->Debug("(tcp) Waiting for a message...");
    this->_socket->async_receive(boost::asio::buffer(*raw_message),
                                 [&, raw_message](
                                     const boost::system::error_code& err,
                                     std::size_t bytes_transferred) {
                                     if (err) {
                                         this->_logger->Error(
                                             "(read tcp) An error occurred: ",
                                             err.message());
                                         this->_is_functional = false;
                                         this->_socket_error_notifier->notify_all();
                                         return;
                                     }
                                     auto package = Common::Network::packet_unpack(
                                         std::string(raw_message->begin(),
                                                     raw_message->end()));
                                     if (package.magic !=
                                         Common::Network::g_MagicNumber)
                                         this->_logger->Error(
                                             "(tcp) Wrong magic number for this message");
                                     else
                                         this->_logger->Info("(tcp) Command: '",
                                                             package.command,
                                                             "' w/ ",
                                                             bytes_transferred);
                                     this->read();
                                 });
}

void
RType::Network::Socket::TCPBoostSocket::write(const Common::Network::TCPPacket& input) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
    std::cout << "RType::Network::Socket::TCPBoostSocket::write::start" << std::endl;
    this->_socket->async_send(buffers,
                              [&](const boost::system::error_code& error,
                                  std::size_t) {
                                  if (error) {
                                      this->_logger->Error(
                                          "[client-> TCPBoostSocket] write ",
                                          error.message());
                                      this->shutdown_socket();
                                      return;
                                  }
                                  std::cout << "Success" << std::endl;
                              });
    std::cout << "RType::Network::Socket::TCPBoostSocket::write::end" << std::endl;
}

bool RType::Network::Socket::TCPBoostSocket::is_functional() {
    return (this->_is_functional);
}
