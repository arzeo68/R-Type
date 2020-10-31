/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef R_TYPE_TCPBOOSTSOCKET_HPP
#define R_TYPE_TCPBOOSTSOCKET_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include "ASocket.hpp"
#include "Common/Log.hpp"

namespace RType::Network::Socket {
    using socket_tcp_t = boost::asio::ip::tcp::socket;

    class TCPBoostSocket : ASocket<socket_tcp_t> {
        public:
        TCPBoostSocket(boost::asio::io_service &service,
                       const Common::Log::Log::shared_log_t &log);
        TCPBoostSocket() = delete;
        ~TCPBoostSocket() override;

        void shutdown() final;

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_TCPBOOSTSOCKET_HPP
