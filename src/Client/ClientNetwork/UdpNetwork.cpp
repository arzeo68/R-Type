#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "UdpNetwork.hpp"
#include "Common/ECS/NetworkPacket.hpp"

namespace Rtype
{

    UDPBoostSocket::UDPBoostSocket(std::string const& host, std::string const &port, boost::asio::io_service& service, std::shared_ptr<std::deque<std::string>>

    & SharedQueue)
        :
        m_Resolver(service), m_udpSocket(service), SharedDataQueue(SharedQueue)
    {
        endpoints = m_Resolver.resolve(host, port);
        _sfUdpSocket = std::make_shared<sf::UdpSocket>();
        _sfUdpSocket->setBlocking(false);
        _addr = host;
        _port = std::atoi(port.c_str());
        _sfUdpSocket->bind(_port);
    }

    void UDPBoostSocket::start_socket() noexcept
    {
        StartConnect(endpoints.begin());
    }

    void UDPBoostSocket::shutdown_socket() noexcept
    {
        stopped = true;
        m_udpSocket.close();
    }

    void UDPBoostSocket::StartConnect(boost::asio::ip::udp::resolver::results_type::iterator endpoint)
    {

    }

    void UDPBoostSocket::HandleConnect(const std::error_code &error, boost::asio::ip::udp::resolver::results_type::iterator endpoint)
    {

    }

    void UDPBoostSocket::write(const RType::Common::Network::TCPPacket& input)
    {
        auto status = _sfUdpSocket->send(&input, sizeof(input), _addr, _port);
        if (status == sf::Socket::Done)
        {
            std::cout << "data succesfully written on :" << _addr << " : " << _port << std::endl;
        }
        else if (status == sf::Socket::NotReady)
        {
//            std::cout << "data succesfully written" << std::endl;
        }
        else if (status == sf::Socket::Partial)
        {
            std::cerr << "PARTIAL" << std::endl;
        }
        else if (status == sf::Socket::Error)
        {
            std::cerr << "ERROR WRITE" << std::endl;
        }
        else
        {
            std::cerr << "OTHER" << std::endl;

        }
    }

    void UDPBoostSocket::start_read()
    {
        //        wait();
        ECS::NetworkPacket data;
        std::size_t received;
        sf::IpAddress sender;
        unsigned short port;
        auto status = _sfUdpSocket->receive(&data, 16, received, sender, port);
        if (status == sf::Socket::NotReady)
        {
//            std::cerr << "not ready" << std::endl;
            return;
        }
        else if (status == sf::Socket::Done)
        {
            std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
            std::cout << "DATA: " << data.id << "  " << data.type << "  " << data.x << "  " << data.y << std::endl;
        }
        else
        {
            std::cerr << " sa a return a autre truc" << std::endl;
        }
    }
}
