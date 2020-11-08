#pragma once

#include <deque>
#include <boost/asio.hpp>

namespace Rtype
{

class Client {
public:
    Client(std::string const& host, std::string const& port, std::shared_ptr<std::deque<std::string>>& SharedQueue);

    ~Client() = default;

    void start();
    void stop();

private:
    void StartConnect(boost::asio::ip::tcp::resolver::results_type::iterator endpoint);
    void HandleConnect(const std::error_code& error, boost::asio::ip::tcp::resolver::results_type::iterator endpoint);

private:
    bool stopped = false;
    boost::asio::io_context m_ioContext;
    boost::asio::ip::tcp::resolver m_Resolver;
    boost::asio::ip::tcp::resolver::results_type endpoints;

    boost::asio::ip::tcp::socket m_tcpSocket;
    std::shared_ptr<std::deque<std::string>> SharedDataQueue;
};

} // namespace Rtype