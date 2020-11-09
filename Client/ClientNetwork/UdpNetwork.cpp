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
        if (stopped)
            return;
        if (!m_udpSocket.is_open())
            StartConnect(++endpoint);
        else if (error)
        {
            m_udpSocket.close();
            StartConnect(++endpoint);
        } else
        {
            // Start Read and Write
        }
    }

    void UDPBoostSocket::write(const RType::Common::Network::TCPPacket& input)
    {
        std::vector<boost::asio::const_buffer> buffers;
        //std::cout << input.size() << std::endl;
        buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
        this->m_udpSocket.async_send(buffers, [this](const boost::system::error_code &error, std::size_t)
        {
            if (error)
            {
//                this->_logger->Error("[client-> UDPBoostSocket] write ",error.message());
                this->shutdown_socket();
                return;
            }
        });
    }

    void UDPBoostSocket::start_read()
    {
    }
}
