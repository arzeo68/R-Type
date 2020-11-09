//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_UDPNETWORK_HPP
#define RTYPE_UDPNETWORK_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <deque>
#include "ASocket.hpp"

namespace Rtype{

    class UDPBoostSocket : public ASocket
    {
        public:

        UDPBoostSocket(std::string const& host, std::string const& port, std::shared_ptr<std::deque<std::string>>& SharedQueue);

        void start_socket() noexcept override;

        void shutdown_socket() noexcept override;

        void start_read() override;

        void write(const std::string &input) override;

        private:
        void StartConnect(boost::asio::ip::udp::resolver::results_type::iterator endpoint);
        void HandleConnect(const std::error_code& error, boost::asio::ip::udp::resolver::results_type::iterator endpoint);

        private:
        bool stopped = false;
        boost::asio::io_context m_ioContext;
        boost::asio::ip::udp::resolver m_Resolver;
        boost::asio::ip::udp::resolver::results_type endpoints;

        boost::asio::ip::udp::socket m_udpSocket;
        std::shared_ptr<std::deque<std::string>> SharedDataQueue;
    };
}

#endif //RTYPE_TCPNETWORK_HPP
