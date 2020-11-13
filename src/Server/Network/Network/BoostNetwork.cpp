/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** BoostNetwork code class implementation
*/

#ifdef _WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif
#include "BoostNetwork.hpp"

RType::Network::BoostNetwork::BoostNetwork(uint32_t port) : _logger(
    std::make_shared<Common::Log::Log>("network",
                                       "network.log",
                                       Common::Log::g_AllLogLevel,
                                       std::ios::trunc)), _thread_pool(1),
    _pending_client(std::make_shared<ThreadSafeQueue<AClient<
        Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t>*>> ()),
    _worker_pending_client([&]() {
        return (!this->_pending_client->empty());
    }, [&]() {
        return (this->_is_running);
    }) {
    this->_rooms.emplace(this->_logger->shared_from_this());
    auto endpoint = boost_asio_tcp::endpoint(boost_asio_tcp::v4(), port);
    this->_router.set_tcp_acceptor(*this->_router.get_io_service(), endpoint);
    printf("Addr: '%s' & port: %i\n", endpoint.address().to_string().c_str(), endpoint.port());
    this->_router.set_udp_endpoint(boost_asio_udp::endpoint(boost_asio_udp::v4(), endpoint.port() + 1));
    this->_router.set_signal_set(*this->_router.get_io_service(), SIGINT);
}

void RType::Network::BoostNetwork::run() {
    this->_logger->Info("Network listening on port ",
                        this->_router.get_io_acceptor()->local_endpoint().port(),
                        " for a new client...");
    this->wait_for_client();
    this->_thread_pool.run([&] {
        this->_router.get_io_service()->run();
    });
    std::string input;
    while (this->_is_running) {
        input.clear();
        std::cin >> input;
        if (input == "exit" || std::cin.eof())
            this->stop();
    }
}

void RType::Network::BoostNetwork::stop() {
    if (!this->_is_running)
        return;
    this->_is_running = false;
    this->_logger->Info("Server start to shut down.");
    this->_logger->Info("Stopping all services...");
    std::for_each(this->_clients.begin(),
                  this->_clients.end(),
                  [](const client_shared_ptr& client) {
                      client->get_tcpsocket()->shutdown_socket();
                      client->get_udpsocket()->shutdown_socket();
                  });
    this->_router.get_io_service()->stop();
    this->_logger->Info("Clearing sockets...");
    this->_clients.clear();
    this->_worker_pending_client.terminate();
    this->_logger->Info("Server stopped!");
}

void RType::Network::BoostNetwork::wait_for_client() {
    this->_logger->Debug("Creating a client & waiting for connection");
    auto client = std::make_shared<BoostClient>(*this->_router.get_io_service(),
                                                *this->_router.get_udp_endpoint(),
                                                this->_logger,
                                                this->_worker_pending_client.share_cv_from_this(),
                                                this->_pending_client->shared_from_this());
    this->_clients.emplace_back(client);
    this->_router.get_io_acceptor()->async_accept(*client->get_tcpsocket()->get_socket(),
                                                  [&, client](const boost::system::error_code& error) {
                                                      if (error) {
                                                          this->_logger->Error(
                                                              "An error occurred: ",
                                                              error.message());
                                                          return;
                                                      }
                                                      this->_logger->Info("(",
                                                                          client,
                                                                          ") Incoming connection from: ",
                                                                          client->get_tcpsocket()->get_socket()->remote_endpoint().address().to_string());
                                                      this->_rooms->add_user(client);
                                                      client->get_tcpsocket()->read();
                                                      this->_logger->Debug(
                                                          "I will recreate a client for the next connection");
                                                      this->wait_for_client();
                                                  });
    this->_logger->Debug("Returning to main run");
}

void RType::Network::BoostNetwork::pre_run() {
    this->_is_running = true;
    this->_worker_pending_client.run([&]() {
        while (!this->_pending_client->empty()) {
            if (this->_pending_client->pop_with_effect([&](AClient<Socket::boost_socket_udp_t, Socket::boost_socket_tcp_t> *client) {
                auto boost_client = dynamic_cast<BoostClient *>(client);
                if (boost_client == nullptr)
                    throw std::exception();
                else {
                    this->remove_client(boost_client);
                    auto removed = this->_rooms->remove_user(boost_client);
                    if (!removed)
                        this->_logger->Error("Cannot remove client from a room");
                    else
                        this->_logger->Debug("Successfully removed client from a room");
                }
            })) {
                this->_logger->Debug("A pending client has been removed");
            } else
                this->_logger->Error("A client cannot be removed");
        }
    });
    this->_router.get_signal_set()->async_wait([self = this->shared_from_this()](
        const boost::system::error_code& error,
        int /*signal*/) {
        if (error)
            self->_logger->Error("Error during catching signals: ",
                                 error.message());
        if (self->_is_running) {
            /**
             * Replace the write of EOF by a real command: "exit"
             */
            #ifdef _WIN_32
            _write(0, "exit", 5);
            #else
            write(0, "exit", 5);
            #endif
        }
    });
}
