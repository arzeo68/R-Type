/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UDPBoostSocket class implementation
*/

#ifndef R_TYPE_UDPBOOSTSOCKET_HPP
#define R_TYPE_UDPBOOSTSOCKET_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include "ASocket.hpp"
#include "Common/Log.hpp"

namespace RType::Network::Socket {
    /**
     * Helper alias used across the network
     */
    using boost_socket_udp_t = boost::asio::ip::udp::socket;

    /**
     * A boost implementation, of ASocket, for UDP communication.
     * The class doesn't contains any other functions than described in ASocket & ISocket.
     */
    class UDPBoostSocket :
        public ASocket<boost_socket_udp_t>,
        public std::enable_shared_from_this<UDPBoostSocket> {
        public:
        UDPBoostSocket(boost::asio::io_service& service,
                       const Common::Log::Log::shared_log_t& log);
        UDPBoostSocket() = delete;
        ~UDPBoostSocket() override;

        void shutdown_socket() noexcept final;
        void start_read() final;
        void write(const Common::Network::TCPPacket& input) final;
        bool is_functional() final;

        private:
        Common::Log::Log::shared_log_t _logger;
    };
}


#endif //R_TYPE_UDPBOOSTSOCKET_HPP
