/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_RTYPE_ASOCKET_
#define SRC_RTYPE_ASOCKET_

#include "Common/Network.hpp"
#include "ISocket.hpp"

namespace RType::Network::Socket {
    /**
     * ASocket is an abstract interface implementing ISocket
     * @tparam T Template correspond to the socket type
     */
    template<class T>
    class ASocket : public ISocket {
        public:
        ~ASocket() override = default;

        /**
         * Override the -> operator to access directly to the socket
         * @return the socket data
         */
        T *operator->() const noexcept {
            return (*this->_socket);
        }

        /**
         *
         */
        using shared_ptr_socket_t = std::shared_ptr<T>;
        /**
         * Get a shared instance of the socket
         * @return A smart pointer of the current stocked socket
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

        protected:
        shared_ptr_socket_t _socket;
    };

    template <typename E>
    class SocketError : public std::exception {
        public:
        explicit SocketError(const E& err) : _err(err) {}

        const char *what() const noexcept override {
            return ("An error occurred in a socket - You might use a build-in function "
                    "to retrieve the error message instead of using what() from this class.");
        }

        // [[maybe_unused]] E get() requires std::is_default_constructible_v<E> {
        [[maybe_unused]] E get() {
            return (this->_err);
        }
        // [[maybe_unused]] E get() const requires std::is_default_constructible_v<E> {
        [[maybe_unused]] E get() const {
            return (this->_err);
        }

        private:
        E _err;
    };
}

#endif
