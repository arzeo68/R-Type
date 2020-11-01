/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "BoostClient.hpp"

RType::Network::BoostClient::BoostClient(boost::asio::io_service& service,
                                         const Common::Log::Log::shared_log_t& log)
    :
    _logger(log) {
    this->_logger->Debug("Create TCP socket");
    this->_tcpsocket = std::make_shared<Socket::TCPBoostSocket>(service, log);
    this->_logger->Debug("Create UDP Socket");
    this->_udpsocket = std::make_shared<Socket::UDPBoostSocket>(service, log);
    this->_logger->Info("Client ", this, " created");
}

RType::Network::BoostClient::~BoostClient() {
    this->_logger->Info("Client ", this, " deleted");
}

void RType::Network::BoostClient::read() {
    this->_tcpsocket->start_read();
    //this->_udpsocket->start_read();
    this->_tcpsocket->write("hello world");
}

