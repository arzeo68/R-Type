/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef R_TYPE_UDPBOOSTSOCKET_HPP
#define R_TYPE_UDPBOOSTSOCKET_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include "ASocket.hpp"
#include "Common/Log.hpp"

namespace RType::Network::Socket {
    using socket_udp_t = boost::asio::ip::udp::socket;

    class UDPBoostSocket : ASocket<socket_udp_t> {
        public:
        UDPBoostSocket(boost::asio::io_service &service,
                       const Common::Log::Log::shared_log_t &log);
        UDPBoostSocket() = delete;
        ~UDPBoostSocket() override;

        void shutdown() final;

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_UDPBOOSTSOCKET_HPP
