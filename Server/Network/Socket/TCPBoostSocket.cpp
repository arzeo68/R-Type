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
    const std::shared_ptr<Common::Log::Log>& log) : _last_error() {
    this->_socket = std::make_shared<socket_tcp_t>(service);
    this->_logger = log;
}

void RType::Network::Socket::TCPBoostSocket::shutdown() noexcept {
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

    if (this->_last_error)
        throw SocketError<boost::system::error_code>(this->_last_error);
    this->_logger->Debug("Waiting for a message...");
    this->_socket->async_receive(boost::asio::buffer(*raw_message),
                                 [self = this->shared_from_this(), raw_message](
                                     const boost::system::error_code& err,
                                     std::size_t bytes_transferred) {
                                     self->_last_error = err;
                                     if (self->_last_error) {
                                         self->_logger->Error(
                                             "(read tcp) An error occurred: ",
                                             err.message());
                                        self->shutdown();
                                        return;
                                     }
                                     self->_logger->Debug("(tcp) Message: '",
                                                          std::string(
                                                              raw_message->begin(),
                                                              raw_message->end()),
                                                          "' w/ ",
                                                          bytes_transferred);
                                     self->start_read();
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
                                  }
                              });
}

bool RType::Network::Socket::TCPBoostSocket::socket_closed() {
    return (this->_socket->is_open());
}
