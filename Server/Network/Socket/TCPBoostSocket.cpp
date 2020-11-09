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

void RType::Network::Socket::TCPBoostSocket::start_read() {
    std::shared_ptr<MessageArr_t> raw_message = std::make_shared<MessageArr_t>();

    this->_logger->Debug("Waiting for a message...");
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
                                     this->_logger->Debug("(tcp) Message: '",
                                                          std::string(
                                                              raw_message->begin(),
                                                              raw_message->end()),
                                                          "' w/ ",
                                                          bytes_transferred);
                                     this->start_read();
                                 });
}

void RType::Network::Socket::TCPBoostSocket::write(const std::string& input) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
    this->_socket->async_send(buffers,
                              [this](const boost::system::error_code& error,
                                     std::size_t) {
                                  if (error) {
                                      this->_logger->Error(
                                          "[client-> TCPBoostSocket] write ",
                                          error.message());
                                      this->shutdown_socket();
                                      return;
                                  }
                              });
}

bool RType::Network::Socket::TCPBoostSocket::is_functional() {
    return (this->_is_functional);
}