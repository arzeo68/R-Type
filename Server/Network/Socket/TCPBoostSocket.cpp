/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <memory>
#include "TCPBoostSocket.hpp"

RType::Network::Socket::TCPBoostSocket::TCPBoostSocket(
    boost::asio::io_service &service, const std::shared_ptr<Common::Log::Log>& log) {
    this->_socket = std::make_shared<socket_tcp_t>(service);
    this->_logger = log;
}

RType::Network::Socket::TCPBoostSocket::~TCPBoostSocket() {
    this->shutdown();
}

void RType::Network::Socket::TCPBoostSocket::shutdown() {
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


