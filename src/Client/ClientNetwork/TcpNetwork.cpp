#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "TcpNetwork.hpp"

namespace Rtype
{

    TCPBoostSocket::TCPBoostSocket(std::string const& host, std::string const &port, std::shared_ptr<std::deque<std::string>>

    & SharedQueue)
    :

    m_ioContext(), m_Resolver(m_ioContext), m_tcpSocket(m_ioContext), SharedDataQueue(SharedQueue)
    {
        endpoints = m_Resolver.resolve(host, port);
    }

    void TCPBoostSocket::start_socket() noexcept
    {
        StartConnect(endpoints.begin());
        m_ioContext.run();
    }

    void TCPBoostSocket::shutdown_socket() noexcept
    {
        stopped = true;
        m_tcpSocket.close();
        m_ioContext.stop();
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
        std::shared_ptr<MessageArr_t> raw_message = std::make_shared<MessageArr_t>();

        m_tcpSocket.async_receive(boost::asio::buffer(*raw_message),
            [&, raw_message](
                const boost::system::error_code& err,
                std::size_t bytes_transferred) {
                if (err) {
                    return;
                }
                auto package = RType::Common::Network::packet_unpack(
                    std::string(raw_message->begin(),
                        raw_message->end()));
                if (package.magic == RType::Common::Network::g_MagicNumber)
                {
                    std::cout << "(tcp) Message: '" << package.command << "' w/ " << bytes_transferred << std::endl;
                }
                this->start_read();
            });
    }
}
