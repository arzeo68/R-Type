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
        virtual void shutdown() = 0;
    };
}

#endif
