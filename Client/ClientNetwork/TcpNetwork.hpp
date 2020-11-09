//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_TCPNETWORK_HPP
#define RTYPE_TCPNETWORK_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <deque>
#include "ASocket.hpp"

namespace Rtype {

    class TCPBoostSocket : public ASocket
    {
        public:

        TCPBoostSocket(std::string const& host, std::string const& port, std::shared_ptr<std::deque<std::string>>& SharedQueue);

        void start_socket() noexcept override;

        void shutdown_socket() noexcept override;

        void start_read() override;

        void write(const RType::Common::Network::TCPPacket &input) override;

        private:
        void StartConnect(boost::asio::ip::tcp::resolver::results_type::iterator endpoint);
        void HandleConnect(const std::error_code& error, boost::asio::ip::tcp::resolver::results_type::iterator endpoint);

        private:
        bool stopped = false;
        boost::asio::io_context m_ioContext;
        boost::asio::ip::tcp::resolver m_Resolver;
        boost::asio::ip::tcp::resolver::results_type endpoints;

        boost::asio::ip::tcp::socket m_tcpSocket;
        std::shared_ptr<std::deque<std::string>> SharedDataQueue;
    };
}

#endif //RTYPE_TCPNETWORK_HPP
