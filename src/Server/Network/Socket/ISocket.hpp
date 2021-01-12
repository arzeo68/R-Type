/*
** EPITECH PROJECT, 2020
** babel
** File description:
** ISocket class implementation
*/

#ifndef SRC_ISOCKET_RTYPE_
#define SRC_ISOCKET_RTYPE_

#include "Common/ECS/NetworkPacket.hpp"
#include "Common/Network.hpp"

namespace RType::Network {
    /**
     * ISocket is an interface which basic function for any socket
     */
    class ISocket {
        public:
        virtual ~ISocket() = default;
        /**
         * The function shutdown the client. It must close the socket and stop all asynchronous operation.
         */
        virtual void shutdown_socket() noexcept = 0;

        /**
         * Read an input from the the socket
         */
        virtual void read() = 0;

        /**
         * Write input to a socket
         * @param input Input to write in the socket
         */
        virtual void write(const Common::Network::TCPPacket&) = 0;
        virtual void write(ECS::NetworkPacket&) = 0;

        /**
         * Indicates if the socket is still functional. Functional, here, means
         * the socket can be used.
         * @return true if the socket is functional
         * @return false if the socket is not functional
         */
        virtual bool is_functional() = 0;
    };
}

#endif
