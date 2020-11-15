//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_ISOCKET_HPP
#define RTYPE_ISOCKET_HPP

#include <memory>
#include <string>
#include "Common/Network.hpp"
/**
 * RType main namespace
 */
namespace RType {
    /**
     * ISocket is an interface whith the basic function for any socket type
     */
    class ISocket {
        public:
        virtual ~ISocket() = default;
        /**
        * The function start the client. It must start the socket and start all asynchronous operation.
        */
        virtual void start_socket() noexcept = 0;
        /**
         * The function shutdown the client. It must close the socket and stop all asynchronous operation.
         */
        virtual void shutdown_socket() noexcept = 0;

        /**
         * start the reading
         */
        virtual void start_read() = 0;

        /**
         * Write input to a socket
         * @param input Input to write in the socket
         */
        virtual void write(const RType::Common::Network::TCPPacket& input) = 0;

        virtual void write(void *data, size_t dataSize) {};
    };
}

#endif //RTYPE_ISOCKET_HPP
