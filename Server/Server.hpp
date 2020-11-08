/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Main class for the binary
*/

#ifndef RTYPE_SERVER_HPP_
#define RTYPE_SERVER_HPP_

#include <memory>
#include "Common/Log.hpp"
#include "Server/Network/Network/ANetwork.hpp"

namespace RType::Server {
    /**
     * The class Server start and stop the server and provide a logger. The server must always exit gracefully.
     */
    template<typename Client = RType::Network::_nullTemplate,
        typename IOService = RType::Network::_nullTemplate,
        typename Acceptor = RType::Network::_nullTemplate,
        typename SignalSet = RType::Network::_nullTemplate>
    class Server {
        public:
        /**
         * The port for the network
         * @param port
         */
        //explicit Server(uint32_t port) :
        explicit Server(uint16_t logLevel = Common::Log::g_AllLogLevel) :
            _logger(std::make_shared<RType::Common::Log::Log>("server", "server.log",
                                                              logLevel,
                                                              std::ios_base::trunc)) {
            //_network(std::make_shared<RType::Network::BoostNetwork>(port,
            //                                            this->_logger->shared_from_this())) {
            this->_logger->Info("Launching server...");
        }
        /**
         * Defined but it only prints an informative message
         */
        ~Server() {
            this->_logger->Info("Server exited gracefully.");
        }
        Server(const Server &obj) = default;


        /**
         *
         * @param ptr
         */
        void create_network(const std::shared_ptr<RType::Network::ANetwork<Client, IOService, Acceptor, SignalSet>>& ptr) {
            this->_network = ptr;
        }

        /**
         * Run the server. The server might be stopped by pressing CTRL+C (or sending SIGINT).
         */
        void run() {
            this->_logger->Info("Server is now running.");
            try {
                this->_network->pre_run();
                this->_network->run();
            } catch (const std::exception &e) {
                this->_logger->Error(e.what());
            }
        }

        private:
        RType::Common::Log::Log::shared_log_t _logger;
        std::shared_ptr<RType::Network::ANetwork<Client, IOService, Acceptor, SignalSet>> _network;
    };
}


#endif //BABEL_SERVER_HPP
