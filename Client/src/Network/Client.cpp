#include <boost/bind.hpp>
#include <Client/include/Network/Client.hpp>

namespace Rtype
{

Client::Client(std::string const& host, std::string const& port, std::shared_ptr<std::deque<std::string>>& SharedQueue)
    : m_ioContext(), m_Resolver(m_ioContext), m_tcpSocket(m_ioContext), SharedDataQueue(SharedQueue)
{
    endpoints = m_Resolver.resolve(host, port);
}

void Client::start()
{
    StartConnect(endpoints.begin());
    m_ioContext.run();
}

void Client::stop()
{
    stopped = true;
    m_tcpSocket.close();
    m_ioContext.stop();
}

void Client::StartConnect(boost::asio::ip::tcp::resolver::results_type::iterator endpoint)
{
    if (endpoint != endpoints.end()) {
        m_tcpSocket.async_connect(endpoint->endpoint(),
            boost::bind(&Client::HandleConnect, this, boost::asio::placeholders::error, endpoint));
    }
}

void Client::HandleConnect(const std::error_code& error, boost::asio::ip::tcp::resolver::results_type::iterator endpoint)
{
    if (stopped)
        return;
    if (!m_tcpSocket.is_open())
        StartConnect(++endpoint);
    else if (error) {
        m_tcpSocket.close();
        StartConnect(++endpoint);
    } else {
        // Start Read and Write
    }
}

} // namespace Rtype
