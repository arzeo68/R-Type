/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ASocket class implementation
*/

#ifndef SRC_RTYPE_ASOCKET_
#define SRC_RTYPE_ASOCKET_

#include <condition_variable>
#include "ISocket.hpp"
#include "Server/Network/Worker/ThreadSafeQueue.hpp"

namespace RType::Network::Socket {
    /**
     * ASocket is an abstract interface implementing ISocket
     * @tparam T Template correspond to the socket type
     */
    template<class T>
    class ASocket : public ISocket {
        public:
        ~ASocket() override = default;
        //ASocket() = default;
        //ASocket(const std::shared_ptr<ThreadSafeQueue<Common::Network::TCPPacket>> shared_queue) {
        //    this->_queue = shared_queue;
        //}

        /**
         * Override the -> operator to access directly to the socket
         * @return the socket data
         */
        T *operator->() const noexcept {
            return (*this->_socket);
        }

        /**
         * Alias for a shared pointer to the socket type
         */
        using shared_ptr_socket_t = std::shared_ptr<T>;

        /**
         * Get a shared instance of the socket
         * @return A shared pointer of the current stocked socket
         */
        [[maybe_unused]] shared_ptr_socket_t get_socket() {
            return (this->_socket);
        }
        /**
         * MessageArr_t is an array of char with the size of TCPPacket.
         * The size is dynamic and depends on TCPPacket. It will be used to write/read
         * on a socket.
         */
        typedef std::array<char, sizeof(Common::Network::TCPPacket)> MessageArr_t;
        typedef std::array<char, sizeof(Common::Network::UDPPacket)> UDPMessageArr_t;


        virtual std::shared_ptr<ThreadSafeQueue<Common::Network::UDPPacket>> get_queue() {
            return (this->_event->shared_from_this());
        };

        protected:
        /**
         * Shared pointer to the socket
         */
        shared_ptr_socket_t _socket;

        /**
         * Indicates if the socket is still functional. Functional, here, means
         * the socket can be used. When the socket is no more functional, the client
         * should exit by using the MessageQueue error and notify the 'condition variable'.
         * See below
         * You can either use this variable as a helper or override the function is_functional
         * and do a custom implementation
         */
        bool _is_functional = true;

        /**
         * A shared pointer to the condition variable hold by the Client worker.
         * @warning You should initialize this variable by yourself but pass an instance instead
         */
        std::shared_ptr<std::condition_variable> _socket_error_notifier;

        std::shared_ptr<ThreadSafeQueue<Common::Network::UDPPacket>> _event;
    };
}

#endif
