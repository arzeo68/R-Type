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
     * The class Server start and stop the network. The server must always exit gracefully.
     * @tparam ClientUDPSocket UDP Socket type for the client
     * @tparam ClientTCPSocket TCP Socket type for the client
     * @tparam IOService See Router documentation
     * @tparam TCPAcceptor See Router documentation
     * @tparam SignalSet See Router documentation
     */
    template<typename ClientUDPSocket,
        typename ClientTCPSocket,
        typename IOService = RType::Network::_nullTemplate,
        typename TCPAcceptor = RType::Network::_nullTemplate,
        typename UDPEndpoint = RType::Network::_nullTemplate,
        typename SignalSet = RType::Network::_nullTemplate>
    class Server {
        public:
        /**
         * Simple constructor for the class
         * @param logLevel The log level which is by default: all log level.
         */
        explicit Server(uint16_t logLevel = Common::Log::g_AllLogLevel) :
            _logger(std::make_shared<RType::Common::Log::Log>("server",
                                                              "server.log",
                                                              logLevel,
                                                              std::ios_base::trunc)) {
            this->_logger->Info("Launching server...");
        }
        /**
         * Defined but it only prints an informative message
         */
        ~Server() {
            this->_logger->Info("Server exited gracefully.");
        }
        Server(const Server& obj) = delete;

        /**
         * Create a network from a shared pointer.
         * @param ptr The shared pointer for the network
         */
        void create_network(
            const std::shared_ptr<RType::Network::ANetwork<ClientUDPSocket, ClientTCPSocket, IOService, TCPAcceptor, UDPEndpoint, SignalSet>>& ptr) {
            this->_network = ptr;
        }

        /**
         * Run the server. The server might be stopped by pressing CTRL+C (or sending SIGINT) or by typing the command "exit".
         */
        void run() {
            this->_logger->Info("Server is now running.");
            try {
                this->_network->pre_run();
                this->_network->run();
            } catch (const std::exception& e) {
                this->_logger->Error(e.what());
            }
        }

        private:
        RType::Common::Log::Log::shared_log_t _logger;
        std::shared_ptr<RType::Network::ANetwork<ClientUDPSocket, ClientTCPSocket, IOService, TCPAcceptor, UDPEndpoint, SignalSet>> _network;
    };
}


#endif //BABEL_SERVER_HPP
