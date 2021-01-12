/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** BoostClient class implementation
*/

#ifndef R_TYPE_BOOSTCLIENT_HPP
#define R_TYPE_BOOSTCLIENT_HPP

#include "AClient.hpp"
#include "Server/Network/Socket/TCPBoostSocket.hpp"
#include "Server/Network/Socket/UDPBoostSocket.hpp"
#include "Server/Network/Worker/ThreadSafeQueue.hpp"

namespace RType::Network {
    /**
     * BoostClient is Boost implementation of AClient using boost's sockets system
     */
    class BoostClient
        :
            public AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> {
        public:
        /**
         * Create a TCP & UDP socket and start running the worker
         * @param service Boost io service for the sockets. Mainly add works to the IO Service.
         * @param log A shared pointer to a logger. Logger is a shared ptr to be thread safe.
         * @param parent_worker_cv The condition variable is used for the socket to notify if there is any error in sockets
         * See also ASocket documentation
         * @param error_queue The queue stack all pending client waiting to be disconnected from the network
         * The network MUST create and pass a shared pointer to this client
         */
        BoostClient(boost::asio::io_service& service,
                    boost::asio::ip::udp::endpoint& endpoint,
                    const Common::Log::Log::shared_log_t& log,
                    const std::shared_ptr<std::condition_variable>& parent_worker_cv,
                    const std::shared_ptr<ThreadSafeQueue<AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> *>>& error_queue);
        /**
         * Defined but used a simply formative message
         */
        ~BoostClient() override;

        void init_write_socket(boost::asio::io_service& service, uint32_t port);

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_BOOSTCLIENT_HPP
