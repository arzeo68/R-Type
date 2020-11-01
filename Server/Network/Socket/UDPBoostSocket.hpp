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

    class UDPBoostSocket
        :
            public ASocket<socket_udp_t>,
            std::enable_shared_from_this<UDPBoostSocket> {
        public:
        UDPBoostSocket(boost::asio::io_service& service,
                       const Common::Log::Log::shared_log_t& log);
        UDPBoostSocket() = delete;
        ~UDPBoostSocket() override;

        void shutdown() noexcept final;
        void start_read() final;
        void write(const std::string& input) final;

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_UDPBOOSTSOCKET_HPP
