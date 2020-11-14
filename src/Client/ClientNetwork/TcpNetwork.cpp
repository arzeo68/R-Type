#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "TcpNetwork.hpp"

namespace Rtype
{

    TCPBoostSocket::TCPBoostSocket(std::string const& host, std::string const &port, boost::asio::io_service& service, std::shared_ptr<std::deque<std::string>>

    & SharedQueue)
    :
        m_Resolver(service), m_tcpSocket(service), SharedDataQueue(SharedQueue)
    {
        endpoints = m_Resolver.resolve(host, port);
    }

    void TCPBoostSocket::start_socket() noexcept
    {
        StartConnect(endpoints.begin());
        //m_ioContext.run();
    }

    void TCPBoostSocket::shutdown_socket() noexcept
    {
        stopped = true;
        m_tcpSocket.close();
        //m_ioContext.stop();
    }

    void TCPBoostSocket::StartConnect(boost::asio::ip::tcp::resolver::results_type::iterator endpoint)
    {
        if (endpoint != endpoints.end())
        {
            m_tcpSocket.async_connect(endpoint->endpoint(), boost::bind(&TCPBoostSocket::HandleConnect, this, boost::asio::placeholders::error, endpoint));
        }
    }

    void TCPBoostSocket::HandleConnect(const std::error_code &error, boost::asio::ip::tcp::resolver::results_type::iterator endpoint)
    {
        if (stopped)
            return;
        if (!m_tcpSocket.is_open())
            StartConnect(++endpoint);
        else if (error)
        {
            m_tcpSocket.close();
            StartConnect(++endpoint);
        } else
        {
            // Start Read and Write
            start_read();
        }
    }

    void TCPBoostSocket::write(const RType::Common::Network::TCPPacket& input)
    {
        std::vector<boost::asio::const_buffer> buffers;
        buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
        this->m_tcpSocket.async_send(buffers, [this](const boost::system::error_code &error, std::size_t)
        {
            if (error)
            {
//                this->_logger->Error("[client-> TCPBoostSocket] write ",error.message());
                this->shutdown_socket();
                return;
            }
        });
    }

    void TCPBoostSocket::start_read()
    {
        std::cout << "Ready to read\n";
        boost::asio::async_read(m_tcpSocket, boost::asio::dynamic_buffer(m_data, 6),
        boost::bind(&TCPBoostSocket::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void TCPBoostSocket::handle_read(const std::error_code& err, size_t s)
    {
        if (!err) {
            std::cout << "read " << *((int *)(m_data.data()) + 1) << "\n";
            m_data.clear();
        } else {
            this->shutdown_socket();
            return;
        }
        start_read();
    }
}
