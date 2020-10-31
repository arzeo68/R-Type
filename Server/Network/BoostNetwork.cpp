/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "BoostNetwork.hpp"

RType::Network::BoostNetwork::BoostNetwork(uint32_t port) {
    this->_router.set_acceptor(*this->_router.get_io_service(),
                               boost_asio_tcp::endpoint(boost_asio_tcp::v4(),
                                                        port));
    this->_router.set_signal_set(*this->_router.get_io_service(), SIGINT);
}

void RType::Network::BoostNetwork::run() {
    //this->_router.get_io_acceptor()->async_accept()
}
