/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** BoostClient class implementation
*/

#include "../Socket/UDPBoostSocket.hpp"
#include "BoostClient.hpp"

RType::Network::BoostClient::BoostClient(boost::asio::io_service& service,
                                         boost::asio::ip::udp::endpoint& endpoint,
                                         const Common::Log::Log::shared_log_t& log,
                                         const std::shared_ptr<std::condition_variable>& parent_worker_cv,
                                         const std::shared_ptr<ThreadSafeQueue<AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> *>>& error_queue)
    :
    AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t>([&]() {
        return (!this->_tcpsocket->is_functional());
    }),
    _logger(log) {
    this->_logger->Debug("Create TCP socket");
    this->_tcpsocket = std::make_shared<Socket::TCPBoostSocket>(service, log,
                                                                this->_worker.share_cv_from_this());
    this->_logger->Debug("Create UDP Socket");
    this->_udpsocket_read = std::make_shared<Socket::UDPBoostSocket>(log, service, endpoint);
    //this->_udpsocket->get_socket()->set_option(boost::asio::ip::udp::socket::reuse_address(true));
    this->_logger->Info("Client ", this, " created");
    this->_socket_error = error_queue;
    this->_worker.run([&, parent_worker_cv]() {
        this->_socket_error->add(this);
        parent_worker_cv->notify_all();
    });
}

RType::Network::BoostClient::~BoostClient() {
    this->_logger->Info("Client ", this, " deleted");
}

void
RType::Network::BoostClient::init_write_socket(boost::asio::io_service& service, uint32_t port) {
    boost::asio::ip::tcp::endpoint tcp_endpoint = this->_tcpsocket->get_socket()->local_endpoint();
    boost::asio::ip::udp::endpoint udp_endpoint(tcp_endpoint.address(), port);
    this->_logger->Info("[Client ", this, "] Socket's port: ", udp_endpoint.port());
    this->_udpsocket_write = std::make_shared<Socket::UDPBoostSocket>(this->_logger->shared_from_this(), service, udp_endpoint);
}
