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
#include "Client/BoostClient.hpp"

namespace RType::Network {
    using boost_asio_tcp = boost::asio::ip::tcp;

    class BoostNetwork
        :
            public ANetwork<BoostClient, boost::asio::io_service, boost_asio_tcp::acceptor,
                boost::asio::signal_set>,
            public std::enable_shared_from_this<BoostNetwork> {

        public:
        explicit BoostNetwork(uint32_t port);
        BoostNetwork() = delete;
        ~BoostNetwork() override = default;
        BoostNetwork(const BoostNetwork&) = delete;

        void run() override;

        void stop() override;

        void add_client(BoostClient&&) override {
        };

        void remove_client(BoostClient&&) override {
        };

        std::list<client_shared_ptr> GetClients() override {
            return (std::list<client_shared_ptr> {});
        };

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_BOOSTNETWORK_HPP
