/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <memory>
#include "UDPBoostSocket.hpp"

RType::Network::Socket::UDPBoostSocket::UDPBoostSocket(
    boost::asio::io_service& service,
    const std::shared_ptr<Common::Log::Log>& log) {
    this->_socket = std::make_shared<boost_socket_udp_t>(service);
    this->_logger = log;
}

RType::Network::Socket::UDPBoostSocket::~UDPBoostSocket() {
    this->shutdown_socket();
}

void RType::Network::Socket::UDPBoostSocket::shutdown_socket() noexcept {
    this->_is_functional = false;
    if (this->_socket->is_open()) {
        boost::system::error_code ec;
        this->_socket->shutdown(
            boost::asio::socket_base::shutdown_type::shutdown_both, ec);
        if (ec)
            this->_logger->Error("[socket-> (udp)] Shutdown: ", ec.message());
        this->_socket->cancel(ec);
        if (ec)
            this->_logger->Error("[socket-> (udp)] Cancel: ", ec.message());
        this->_socket->close(ec);
        if (ec)
            this->_logger->Error("[socket-> (udp)] Close: ", ec.message());
        this->_logger->Debug(this, " socket (udp) successfully closed");
    } else
        this->_logger->Debug(this, " socket (udp) already closed");
}

void RType::Network::Socket::UDPBoostSocket::start_read() {
    std::shared_ptr<MessageArr_t> raw_message = std::make_shared<MessageArr_t>();

    this->_socket->async_receive(boost::asio::buffer(*raw_message),
                                 [self = this->shared_from_this(), raw_message](
                                     const boost::system::error_code& err,
                                     std::size_t bytes_transferred) {
                                     if (err) {
                                         self->_logger->Error(
                                             "(read udp) An error occurred: ",
                                             err.message());
                                     }
                                     self->_logger->Debug("(udp) Message: '",
                                                          std::string(
                                                              raw_message->begin(),
                                                              raw_message->end()),
                                                          "' w/ ",
                                                          bytes_transferred);
                                     self->start_read();
                                 });
}

void RType::Network::Socket::UDPBoostSocket::write(const std::string& input) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
    this->_socket->async_send(buffers,
                              [this](const boost::system::error_code& error,
                                     std::size_t) {
                                  if (error) {
                                      this->_logger->Error(
                                          "[client-> UDPBoostSocket] write ",
                                          error.message());
                                  }
                              });
}

bool RType::Network::Socket::UDPBoostSocket::is_functional() {
    return (this->_is_functional);
}
