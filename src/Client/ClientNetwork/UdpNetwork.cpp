#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "UdpNetwork.hpp"

RType::Common::Network::TCPPacket RType::Common::Network::packet_unpack(const std::string& str) {
    return *(struct Common::Network::TCPPacket *) str.data();
}

namespace Rtype
{

    UDPBoostSocket::UDPBoostSocket(std::string const& host, std::string const &port, boost::asio::io_service& service, std::shared_ptr<std::deque<std::string>>

    & SharedQueue)
        :
        m_Resolver(service), m_udpSocket(service), SharedDataQueue(SharedQueue)
    {
        endpoints = m_Resolver.resolve(host, port);
    }

    void UDPBoostSocket::start_socket() noexcept
    {
        StartConnect(endpoints.begin());
        //m_ioContext.run();
    }

    void UDPBoostSocket::shutdown_socket() noexcept
    {
        stopped = true;
        m_udpSocket.close();
        //m_ioContext.stop();
    }

    void UDPBoostSocket::StartConnect(boost::asio::ip::udp::resolver::results_type::iterator endpoint)
    {
        if (endpoint != endpoints.end())
        {
            m_udpSocket.async_connect(endpoint->endpoint(), boost::bind(&UDPBoostSocket::HandleConnect, this, boost::asio::placeholders::error, endpoint));
            _endpoint = endpoint->endpoint();
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
            printf("(%p) Failed w/: '%s'\n", this, error.message().c_str());
            StartConnect(++endpoint);
        } else
        {
            // Start Read and Write
            printf("Socket: %p\n", this);
            start_read();
        }
    }

    void UDPBoostSocket::write(const RType::Common::Network::TCPPacket& input)
    {
        std::vector<boost::asio::const_buffer> buffers;
        std::cout << "Writing smth" << std::endl;
        buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));

        this->m_udpSocket.async_send_to(buffers, _endpoint, [this](const boost::system::error_code &error, std::size_t)
        {
            printf("error? %i\n", error.value());
            if (error)
            {
                std::cerr << "Err: " << error.message() << std::endl;
                //this->_logger->Error("[client-> UDPBoostSocket] write ",error.message());
                this->shutdown_socket();
                return;
            } else
                std::cout << "Message sent, no error" << std::endl;
        });
    }

    void UDPBoostSocket::wait() {
        std::shared_ptr<std::array<char, 28>> raw_message = std::make_shared<std::array<char, 28>>();

        std::cout << "(udp) Waiting for a message..." << std::endl;
        boost::system::error_code err;
        this->m_udpSocket.bind(this->_endpoint, err);
        if (err)
            std::cerr << "ERROR 0:  " << err.message() << std::endl;
        this->m_udpSocket.async_receive(boost::asio::buffer(*raw_message),
                                        [&, raw_message](
                                            const boost::system::error_code& err,
                                            std::size_t) {
                                            if (err) {
                                                std::cerr << "error 1  " << err.message() << std::endl;
                                            }
                                            else
                                            {
                                                std::cout << " ca marche bien zebi" << std::endl;
                                            }
                                            this->wait();
                                        });
        std::cout << "exiting this shitty function" << std::endl;
    }

    void UDPBoostSocket::start_read()
    {
        wait();
    }
}
