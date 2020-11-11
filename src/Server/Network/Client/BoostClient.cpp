/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** BoostClient class implementation
*/

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
                                                                this->_worker_is_active.share_cv_from_this());
    this->_logger->Debug("Create UDP Socket");
    this->_udpsocket = std::make_shared<Socket::UDPBoostSocket>(log, service, endpoint);
    //this->_udpsocket->get_socket()->set_option(boost::asio::ip::udp::socket::reuse_address(true));
    this->_logger->Info("Client ", this, " created");
    this->_socket_error = error_queue;
    this->_worker_is_active.run([&, parent_worker_cv]() {
        this->_socket_error->add(this);
        parent_worker_cv->notify_all();
    });
}

RType::Network::BoostClient::~BoostClient() {
    this->_logger->Info("Client ", this, " deleted");
}
