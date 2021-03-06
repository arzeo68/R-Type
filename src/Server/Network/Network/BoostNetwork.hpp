/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** BoostNetwork class implementation
*/

#ifndef R_TYPE_BOOSTNETWORK_HPP
#define R_TYPE_BOOSTNETWORK_HPP

#include <boost/asio.hpp>
#include "ANetwork.hpp"
#include "../Client/BoostClient.hpp"
#include "ThreadPool.hpp"
#include "../Worker/Worker.hpp"

namespace RType::Network {
    using boost_asio_tcp = boost::asio::ip::tcp;
    using boost_asio_udp = boost::asio::ip::udp;

    /**
     * A boost implementation of the ANetwork. The class doesn't contains any
     * other functions than described in ANetwork & INetwork.
     */
    class BoostNetwork
        :
            public ANetwork<Socket::boost_socket_udp_t,
                Socket::boost_socket_tcp_t,
                boost::asio::io_service,
                boost_asio_tcp::acceptor,
                boost_asio_udp::endpoint,
                boost::asio::signal_set>,
            public std::enable_shared_from_this<BoostNetwork> {

        public:
        explicit BoostNetwork(uint32_t port);
        BoostNetwork() = delete;
        ~BoostNetwork() override = default;
        BoostNetwork(const BoostNetwork&) = delete;

        void run() override;
        void stop() override;
        void wait_for_client() override;
        void pre_run() override;

        private:
        Common::Log::Log::shared_log_t _logger;
        ThreadPool _thread_pool;
        std::shared_ptr<ThreadSafeQueue<AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> *>> _pending_client;
        Worker _worker_pending_client;
        uint64_t _global_port = 4244;
    };
}


#endif //R_TYPE_BOOSTNETWORK_HPP
