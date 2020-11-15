#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "UdpNetwork.hpp"
#include "Common/ECS/NetworkPacket.hpp"

namespace RType
{

    void UDPBoostSocket::start_socket() noexcept
    {
    }

    void UDPBoostSocket::shutdown_socket() noexcept
    {
    }

    void UDPBoostSocket::write(const RType::Common::Network::TCPPacket& input)
    {
        auto status = _sfUdpSocket->send(&input, sizeof(input), _addr, _port);
        if (status == sf::Socket::Done)
        {
            //std::cout << "data succesfully written on :" << _addr << " : " << _port << std::endl;
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
        auto status = _sfUdpSocket->receive(&data, sizeof(data), received, sender, port);
        if (status == sf::Socket::NotReady)
        {
//            std::cerr << "not ready" << std::endl;
            return;
        }
        else if (status == sf::Socket::Done)
        {
            std::shared_ptr<NetworkEvent> event = std::make_shared<NetworkEvent>(data);
            subject.notify(EVENT, event);
        }
        else
        {
            std::cerr << " ça a return a autre truc" << std::endl;
        }
    }

    void UDPBoostSocket::write(void *data, size_t dataSize)
    {
        auto status = _sfUdpSocket->send(data, dataSize, _addr, _port);
        if (status == sf::Socket::Done)
        {
            //std::cout << "data succesfully written on :" << _addr << " : " << _port << std::endl;
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
}
