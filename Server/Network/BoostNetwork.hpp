/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef R_TYPE_BOOSTNETWORK_HPP
#define R_TYPE_BOOSTNETWORK_HPP

#include <boost/asio.hpp>
#include "ANetwork.hpp"

namespace RType::Network {
    class Client {
        public:
        Client() = default;
    };

    using boost_asio_tcp = boost::asio::ip::tcp;

    class BoostNetwork
        :
            public ANetwork<Client, boost::asio::io_service, boost_asio_tcp::acceptor,
                boost::asio::signal_set> {

        public:
        explicit BoostNetwork(uint32_t port);
        BoostNetwork() = delete;
        ~BoostNetwork() override = default;
        BoostNetwork(const BoostNetwork&) = delete;

        void run() override;

        void stop() override {
        };

        void add_client(Client&&) override {
        };

        void remove_client(Client&&) override {
        };

        std::list<client_shared_ptr> GetClients() override {
            return (std::list<client_shared_ptr>{});
        };
    };
}


#endif //R_TYPE_BOOSTNETWORK_HPP
