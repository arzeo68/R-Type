#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "UdpNetwork.hpp"

namespace Rtype
{

    UDPBoostSocket::UDPBoostSocket(std::string const& host, std::string const &port, std::shared_ptr<std::deque<std::string>>

    & SharedQueue)
    :

    m_ioContext(), m_Resolver(m_ioContext), m_udpSocket(m_ioContext), SharedDataQueue(SharedQueue)
    {
        endpoints = m_Resolver.resolve(host, port);
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
        boost::asio::ip::udp::resolver::iterator iter = m_Resolver.resolve(query);
        this->_endpoint = *iter;
    }

    void UDPBoostSocket::start_socket() noexcept
    {
        StartConnect(endpoints.begin());
        m_ioContext.run();
    }

    void UDPBoostSocket::shutdown_socket() noexcept
    {
        stopped = true;
        m_udpSocket.close();
        m_ioContext.stop();
    }

    void UDPBoostSocket::StartConnect(boost::asio::ip::udp::resolver::results_type::iterator endpoint)
    {
        if (endpoint != endpoints.end())
        {
            m_udpSocket.async_connect(endpoint->endpoint(), boost::bind(&UDPBoostSocket::HandleConnect, this, boost::asio::placeholders::error, endpoint));
        }
    }

    void UDPBoostSocket::HandleConnect(const std::error_code &error, boost::asio::ip::udp::resolver::results_type::iterator endpoint)
    {
        if (stopped) {
            std::cerr << "truc is stopped" << std::endl;
            return;
        }
        if (!m_udpSocket.is_open()) {
            std::cerr << "SOCKET IS NOT OPEN" << std::endl;
            StartConnect(++endpoint);
        }
        else if (error)
        {
            std::cerr << "HandleConnect err: " << error.message() << std::endl;
            m_udpSocket.close();
            StartConnect(++endpoint);
        } else
        {
            std::cout << "SO THIS IS CONNECTED" << std::endl;
            // Start Read and Write
            this->write({RType::Common::Network::g_MagicNumber, 66});
        }
    }

    void UDPBoostSocket::write(const RType::Common::Network::TCPPacket& input)
    {
        std::vector<boost::asio::const_buffer> buffers;
        std::cout << "Writing smth" << std::endl;
        buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
        //boost::asio::ip::udp::endpoint endpoint = *m_Resolver.resolve(boost::asio::ip::udp::v4(), "127.0.0.1", "").begin();
        //this->m_udpSocket.send_to(buffers, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 4243));
        auto k = this->m_udpSocket.send_to(buffers, this->_endpoint);
        std::cout << "size: " << k << std::endl;
        //this->m_udpSocket.send(buffers, [this](const boost::system::error_code &error, std::size_t)
        //{
        //    if (error)
        //    {
        //        std::cerr << "Err: " << error.message() << std::endl;
        //        this->_logger->Error("[client-> UDPBoostSocket] write ",error.message());
                //this->shutdown_socket();
                //return;
            //} else
            //    std::cerr << "Message sent, no error" << std::endl;
        //});
    }

    void UDPBoostSocket::start_read()
    {
    }
}
