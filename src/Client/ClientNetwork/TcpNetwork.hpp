//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_TCPNETWORK_HPP
#define RTYPE_TCPNETWORK_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <deque>
#include "ASocket.hpp"
/**
 * main namespace
 */
namespace Rtype {
    /**
     * implementation of ISocket for a TCP boost socket
     */
    class TCPBoostSocket : public ASocket
    {
        public:
        /**
         *  class contructor
         * @param host server ip
         * @param port server port
         * @param SharedQueue queue in which the socket will stored the message received
         */
        TCPBoostSocket(std::string const& host, std::string const& port,
                       boost::asio::io_service& service,
                       std::shared_ptr<std::deque<std::string>>& SharedQueue);
        /**
         * start the socket
         */
        void start_socket() noexcept override;
        /**
         * stop the socket
         */
        void shutdown_socket() noexcept override;
        /**
         * start reading
         */
        void start_read() override;
        /**
         * write into the socket
         */
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
