/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Main file for the server part
*/

#include <iostream>
#include "Server.hpp"
#include "Network/Client/BoostClient.hpp"
#include "Server/Network/BoostNetwork.hpp"

template<typename A>
concept test_concept = std::is_integral_v<A>;

template<typename A>
void __attribute__((unused)) helloFunc() requires test_concept<A> {
}

int main(const int ac, const char **av) {
    uint32_t port = 4242;
    if (ac != 1)
        port = std::stoi(av[1], nullptr);

    try {
        RType::Server::Server<RType::Network::BoostClient, boost::asio::io_service, boost::asio::ip::tcp::acceptor,
                boost::asio::signal_set> server;
        server.create_network(std::make_shared<RType::Network::BoostNetwork>(port));
        server.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
