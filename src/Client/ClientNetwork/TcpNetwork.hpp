//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_TCPNETWORK_HPP
#define RTYPE_TCPNETWORK_HPP

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <vector>
#include <deque>
#include "ASocket.hpp"
#include "Server/Network/Worker/ThreadSafeQueue.hpp"
/**
 * main namespace
 */
namespace RType {
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
                       const std::shared_ptr<RType::Network::ThreadSafeQueue<int>>& SharedQueue);
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
        void handle_read(const std::error_code& error, size_t s);

        private:
        bool stopped = false;
        boost::asio::io_context m_ioContext;
        boost::asio::ip::tcp::resolver m_Resolver;
        boost::asio::ip::tcp::resolver::results_type endpoints;

        boost::asio::ip::tcp::socket m_tcpSocket;
        std::shared_ptr<RType::Network::ThreadSafeQueue<int>> SharedDataQueue;
        std::vector<char> m_data;
    };
}

#endif //RTYPE_TCPNETWORK_HPP
