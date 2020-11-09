/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef R_TYPE_BOOSTCLIENT_HPP
#define R_TYPE_BOOSTCLIENT_HPP

#include "AClient.hpp"
#include "Server/Network/Socket/TCPBoostSocket.hpp"
#include "Server/Network/Socket/UDPBoostSocket.hpp"
#include "Server/Network/Worker/ThreadSafeQueue.hpp"

namespace RType::Network {
    class BoostClient
        :
            public AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> {
        public:
        BoostClient(boost::asio::io_service& service,
                    const Common::Log::Log::shared_log_t& log,
                    const std::shared_ptr<std::condition_variable>& parent_worker_cv,
                    const std::shared_ptr<ThreadSafeQueue<AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> *>>& error_queue);
        ~BoostClient() override;
        //void read() override;

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_BOOSTCLIENT_HPP
