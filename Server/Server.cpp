/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Main class for the binary
*/

#include "Server.hpp"

template<typename Client, typename IOService, typename Acceptor, typename SignalSet>
void RType::Server::Server<Client, IOService, Acceptor, SignalSet>::run() {
    this->_logger->Info("Server is now running.");
    try {
        //this->_network->PreRun();
        this->_network->run();
    } catch (const std::exception &e) {
        this->_logger->Error(e.what());
    }
}

template<typename Client, typename IOService, typename Acceptor, typename SignalSet>
RType::Server::Server<Client, IOService, Acceptor, SignalSet>::~Server() {
    this->_logger->Info("Server exited gracefully.");
}
template<typename Client, typename IOService, typename Acceptor, typename SignalSet>
void RType::Server::Server<Client, IOService, Acceptor, SignalSet>::create_network(
    const std::shared_ptr<RType::Network::ANetwork<Client, IOService, Acceptor, SignalSet>>& ptr) {
    this->_network = ptr;
}
