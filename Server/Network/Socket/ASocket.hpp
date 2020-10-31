/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_RTYPE_ASOCKET_
#define SRC_RTYPE_ASOCKET_

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

        using shared_ptr_socket_t = std::shared_ptr<T>;
        /**
         * Get a shared instance of the socket
         * @return A smart pointer of the current stocked socket
         */
        [[maybe_unused]] shared_ptr_socket_t get_socket() {
            return (this->_socket);
        }

        protected:
        shared_ptr_socket_t _socket;
    };
}

#endif
