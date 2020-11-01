/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "BoostNetwork.hpp"

RType::Network::BoostNetwork::BoostNetwork(uint32_t port) : _logger(
    std::make_shared<Common::Log::Log>("network", "network.log")) {
    this->_router.set_acceptor(*this->_router.get_io_service(),
                               boost_asio_tcp::endpoint(boost_asio_tcp::v4(),
                                                        port));
    this->_router.set_signal_set(*this->_router.get_io_service(), SIGINT);
}

void RType::Network::BoostNetwork::run() {
    this->_logger->Info("Network listening on port ",
                        this->_router.get_io_acceptor()->local_endpoint().port());
    auto new_client = std::make_shared<BoostClient>(
        *this->_router.get_io_service(),
        this->_logger);
    this->_clients.emplace_back(new_client);
    this->_router.get_io_acceptor()->async_accept(
        *new_client->get_tcpsocket()->get_socket(),
        [self = this->shared_from_this(), client = new_client](
            const boost::system::error_code& error) {
            if (error) {
                self->_logger->Error("An error occurred: ", error.message());
                return;
            }
            self->_logger->Info(client, " - Incoming connection from: ",
                                client->get_tcpsocket()->get_socket()->remote_endpoint().address().to_string());
            client->read();
        });
    this->_router.get_io_service()->run();
}
void RType::Network::BoostNetwork::stop() {
    std::for_each(this->_clients.begin(), this->_clients.end(),
                  [](const client_shared_ptr& client) {
                      client->get_tcpsocket()->shutdown();
                      client->get_udpsocket()->shutdown();
                  });
}
