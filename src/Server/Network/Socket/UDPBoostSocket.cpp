/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <boost/asio/ip/multicast.hpp>
#include <memory>
#include "UDPBoostSocket.hpp"

RType::Network::Socket::UDPBoostSocket::UDPBoostSocket(
    const std::shared_ptr<Common::Log::Log>& log,
    boost::asio::io_service& service,
    const boost::asio::ip::udp::endpoint& endpoint) : _endpoint(endpoint) {
    this->_socket = std::make_shared<boost_socket_udp_t>(service);
    this->_socket->open(endpoint.protocol());
    this->_socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));
    this->_logger = log;
    this->_event = std::make_shared<ThreadSafeQueue<Common::Network::UDPPacket>>();
}

RType::Network::Socket::UDPBoostSocket::~UDPBoostSocket() {
    //this->shutdown_socket();
}

void RType::Network::Socket::UDPBoostSocket::shutdown_socket() noexcept {
    this->_is_functional = false;
    if (this->_socket->is_open()) {
        boost::system::error_code ec;
        this->_socket->shutdown(
            boost::asio::socket_base::shutdown_type::shutdown_both, ec);
        if (ec)
            this->_logger->Error("[socket-> (udp)] Shutdown: ", ec.message());
        this->_socket->cancel(ec);
        if (ec)
            this->_logger->Error("[socket-> (udp)] Cancel: ", ec.message());
        this->_socket->close(ec);
        if (ec)
            this->_logger->Error("[socket-> (udp)] Close: ", ec.message());
        this->_logger->Debug(this, " socket (udp) successfully closed");
    } else
        this->_logger->Debug(this, " socket (udp) already closed");
}

void RType::Network::Socket::UDPBoostSocket::read() {
    std::shared_ptr<UDPMessageArr_t> raw_message = std::make_shared<UDPMessageArr_t>();

    this->_logger->Debug("(udp) Waiting for a message...");
    boost::system::error_code err;
    boost::asio::ip::udp::endpoint endn(boost::asio::ip::address::from_string("127.0.0.1"), 4243);
    this->_socket->bind(endn, err);
    this->_socket->async_receive_from(boost::asio::buffer(*raw_message),
                                endn,
                                 [&, raw_message](
                                     const boost::system::error_code& err,
                                     std::size_t bytes_transferred) {
                                     if (err) {
                                         this->_logger->Error(
                                             "(read udp) An error occurred: ",
                                             err.message());
                                         return;
                                     }
                                     auto package = Common::Network::UDPpacket_unpack(
                                         std::string(raw_message->begin(),
                                                     raw_message->end()));
                                     if (package.magic !=
                                         Common::Network::g_MagicNumber)
                                         this->_logger->Error(
                                             "(udp) Wrong magic number for this message");
                                     else {
                                         this->_event->add(package);
                                         this->_logger->Info("(udp) USER: '",
                                                             package.networkID,
                                                             "' w/ ",
                                                             bytes_transferred);
                                     }
                                     this->read();
                                 });
}

void
RType::Network::Socket::UDPBoostSocket::write(const Common::Network::TCPPacket& input) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
    this->_socket->async_send(buffers,
                              [this](const boost::system::error_code& error,
                                     std::size_t size) {
                                  if (error) {
                                      this->_logger->Error(
                                          "[client-> UDPBoostSocket] TCPPacket write ",
                                          error.message());
                                  } else {
                                      this->_logger->Debug(
                                          "[client-> UDPBoostSocket] TCPPacket write w/ ", size);
                                  }
                              });
}

void
RType::Network::Socket::UDPBoostSocket::write(ECS::NetworkPacket& input) {
    std::vector<boost::asio::const_buffer> buffers;
    buffers.emplace_back(boost::asio::buffer(&input, sizeof(input)));
    this->_socket->async_send_to(buffers, this->_endpoint,
                              [this](const boost::system::error_code& error,
                                     std::size_t) {
                                  if (error) {
                                      this->_logger->Error(
                                          "[client-> UDPBoostSocket] NetworkPacket write ",
                                          error.message());
                                  }
                              });

}

bool RType::Network::Socket::UDPBoostSocket::is_functional() {
    return (this->_is_functional);
}

std::shared_ptr<RType::Network::ThreadSafeQueue<RType::Common::Network::UDPPacket>>
RType::Network::Socket::UDPBoostSocket::get_queue() {
    return (this->_event->shared_from_this());
}
