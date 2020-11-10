/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ACLIENT_HPP_
#define SRC_RTYPE_ACLIENT_HPP_

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
#include "../Worker/ThreadSafeQueue.hpp"
#include "../Socket/ASocket.hpp"
#include "../Worker/Worker.hpp"

namespace RType::Network {
    template<typename UDPSocket, typename TCPSocket>
    class AClient {
        public:
        AClient(const std::function<bool()>& u) : _worker_is_active(u) {
        }
        AClient(const std::function<bool()>& u,
                const std::function<bool()>& l) : _worker_is_active(u, l) {
        }
        virtual ~AClient() {
            this->_worker_is_active.terminate();
        };
        /**
         *
         * @return
         */
        std::shared_ptr<Socket::ASocket<UDPSocket>> get_udpsocket() {
            return (this->_udpsocket);
        }

        /**
         *
         * @return
         */
        std::shared_ptr<Socket::ASocket<TCPSocket>> get_tcpsocket() {
            return (this->_tcpsocket);
        }

        /**
         *
         */
        //virtual void read() = 0;

        protected:
        Worker _worker_is_active;
        std::shared_ptr<Socket::ASocket<UDPSocket>> _udpsocket;
        std::shared_ptr<Socket::ASocket<TCPSocket>> _tcpsocket;
        std::shared_ptr<ThreadSafeQueue<AClient<UDPSocket, TCPSocket> *>> _socket_error;
    };
}
#endif
