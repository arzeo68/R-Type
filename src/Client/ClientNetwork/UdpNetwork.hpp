//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_UDPNETWORK_HPP
#define RTYPE_UDPNETWORK_HPP

#include <SFML/Network.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <deque>
#include <src/Client/ObserverPattern/Subject.hpp>
#include "ASocket.hpp"
#include "Common/ECS/NetworkPacket.hpp"
/**
 * main namespace
 */
namespace RType{
    enum packageType {
        EVENT
    };

    class NetworkEvent : public Observer::IEvent {
        public:
            NetworkEvent(ECS::NetworkPacket& p)
                : data(p)
            { }

            ECS::NetworkPacket data{};
    };

    /**
     * implementation of ISocket for a UDP boost socket
     */
    class UDPBoostSocket : public ASocket
    {
        public:
        /**
         *  class contructor
         * @param host server ip
         * @param port server port
         * @param SharedQueue queue in which the socket will stored the message received
         */
        template<typename func>
        UDPBoostSocket(std::string const& host, std::string const& port,
                       boost::asio::io_service& service, func&& handler)
        {
            _sfUdpSocket = std::make_shared<sf::UdpSocket>();
            _sfUdpSocket->setBlocking(false);
            _addr = host;
            _port = std::atoi(port.c_str());
            _sfUdpSocket->bind(_port);
            subject.registerObserver(EVENT, handler);
        }
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
        void write(const RType::Common::Network::TCPPacket& input) override;

        private:
        void write(void *data, size_t dataSize) override;

        private:

        bool stopped = false;

        std::shared_ptr<sf::UdpSocket> _sfUdpSocket;
        unsigned short _port;
        sf::IpAddress _addr;
        Observer::Subject<packageType> subject;
    };
}

#endif //RTYPE_TCPNETWORK_HPP
