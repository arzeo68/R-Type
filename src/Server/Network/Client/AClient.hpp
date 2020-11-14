/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** AClient class implementation
*/

#ifndef SRC_RTYPE_ACLIENT_HPP_
#define SRC_RTYPE_ACLIENT_HPP_

#include <memory>
#include <condition_variable>
#include <utility>
#include "../Worker/ThreadSafeQueue.hpp"
#include "../Worker/Worker.hpp"
#include "../Socket/ASocket.hpp"

namespace RType::Network {
    template<typename UDPSocket, typename TCPSocket>
    class AClient {
        public:
        /**
         * Construct an AClient and initialize the class' worker.
         * @param u A function with the signature: bool function(void)
         * The function unlock the thread when it wakes up.
         * - The function MUST returns TRUE to unlock the thread
         * - If the function returns FALSE, the thread fall back to sleep
         */
        AClient() = delete;
        AClient(const std::function<bool()>& u) : _worker(u) {
        }
        /**
         *
         * @param u Same as @link{#AClient} (above)
         * @param l A function with the signature: bool function(void)
         * The function is used to repeat the thread's task until the function returns false
         * - The function MUST returns TRUE to stop the repeating task
         * - The thread must be awake and the function @link{u} must have returned TRUE
         */
        AClient(const std::function<bool()>& u,
                const std::function<bool()>& l) : _worker(u, l) {
        }
        AClient(const AClient<UDPSocket, TCPSocket>&) = delete;
        /**
         * Virtual destructor which terminate the worker's thread.
         */
        virtual ~AClient() {
            this->_worker.terminate();
        };
        /**
         * Get the client's TCP socket
         * @return A shared pointer to the UDP Socket
         */
        std::shared_ptr<Socket::ASocket<UDPSocket>> get_udpsocket_read() {
            return (this->_udpsocket_read);
        }
        /**
         * Get the client's TCP socket
         * @return A shared pointer to the UDP Socket
         */
        std::shared_ptr<Socket::ASocket<UDPSocket>> get_udpsocket_write() {
            return (this->_udpsocket_write);
        }

        /**
         * Get the client's TCP socket
         * @return A shared pointer to the TCP Socket
         */
        std::shared_ptr<Socket::ASocket<TCPSocket>> get_tcpsocket() {
            return (this->_tcpsocket);
        }

        protected:
        Worker _worker;
        std::shared_ptr<Socket::ASocket<UDPSocket>> _udpsocket_write;
        std::shared_ptr<Socket::ASocket<UDPSocket>> _udpsocket_read;
        std::shared_ptr<Socket::ASocket<TCPSocket>> _tcpsocket;
        std::shared_ptr<ThreadSafeQueue<AClient<UDPSocket, TCPSocket> *>> _socket_error;
    };
}
#endif
