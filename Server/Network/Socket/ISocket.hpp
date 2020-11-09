/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_ISOCKET_RTYPE_
#define SRC_ISOCKET_RTYPE_

#include <memory>

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
        virtual void start_read() = 0;

        /**
         * Write input to a socket
         * @param input Input to write in the socket
         */
        virtual void write(const std::string& input) = 0;

        virtual bool is_functional() = 0;
    };
}

#endif
