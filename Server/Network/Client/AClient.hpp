/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ACLIENT_HPP_
#define SRC_RTYPE_ACLIENT_HPP_

#include <memory>

namespace RType::Network {
    template<typename UDPSocket, typename TCPSocket>
    class AClient {
        public:
        virtual ~AClient() = default;

        /**
         *
         * @return
         */
        std::shared_ptr<UDPSocket> get_udpsocket() {
            return (this->_udpsocket);
        }

        /**
         *
         * @return
         */
        std::shared_ptr<TCPSocket> get_tcpsocket() {
            return (this->_tcpsocket);
        }

        virtual void read() = 0;

        protected:
        std::shared_ptr<UDPSocket> _udpsocket;
        std::shared_ptr<TCPSocket> _tcpsocket;
    };
}
#endif
