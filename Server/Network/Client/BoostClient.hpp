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
            public AClient<Socket::UDPBoostSocket, Socket::TCPBoostSocket> {
        public:
        BoostClient(boost::asio::io_service& service,
                    const Common::Log::Log::shared_log_t& log);
        ~BoostClient() override;
        void read() override;

        private:
        Common::Log::Log::shared_log_t _logger;
        std::shared_ptr<ThreadSafeQueue<BoostClient*>> _remove_queue;
    };
}


#endif //R_TYPE_BOOSTCLIENT_HPP
