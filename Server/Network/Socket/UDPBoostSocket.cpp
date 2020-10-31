/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <memory>
#include "UDPBoostSocket.hpp"

RType::Network::Socket::UDPBoostSocket::UDPBoostSocket(
    boost::asio::io_service &service, const std::shared_ptr<Common::Log::Log>& log) {
    this->_socket = std::make_shared<socket_udp_t>(service);
    this->_logger = log;
}

RType::Network::Socket::UDPBoostSocket::~UDPBoostSocket() {
    this->shutdown();
}

void RType::Network::Socket::UDPBoostSocket::shutdown() {
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
