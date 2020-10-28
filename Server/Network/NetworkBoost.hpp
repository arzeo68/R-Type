/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef R_TYPE_NETWORKBOOST_HPP
#define R_TYPE_NETWORKBOOST_HPP

#include <boost/asio.hpp>
#include "ANetwork.hpp"

namespace RType::Network {
    class Client {
        public:
        Client() = default;
    };

    using boost_asio_tcp = boost::asio::ip::tcp;

    class NetworkBoost
        :
            public ANetwork<Client, boost::asio::io_service, boost_asio_tcp::acceptor,
                boost::asio::signal_set> {

        public:
        NetworkBoost(uint32_t port) {
            this->_router.set_acceptor(
                boost_asio_tcp::acceptor(*this->_router.get_io_service(),
                                         boost_asio_tcp::endpoint(
                                             boost_asio_tcp::v4(), port)));
        }
        void run() override {
        };
        void stop() override {
        };
        void add_client(Client &&) override {
        };
        void remove_client(Client &&) override {
        };
        std::list<client_shared_ptr> GetClients() override {
            return (std::list<client_shared_ptr> {});
        };
    };
}


#endif //R_TYPE_NETWORKBOOST_HPP
