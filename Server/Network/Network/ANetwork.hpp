/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ANETWORK_HPP_
#define SRC_RTYPE_ANETWORK_HPP_

#include <mutex>
#include <list>
#include <algorithm>
#include "Server/Network/Room.hpp"
#include "Router.hpp"
#include "INetwork.hpp"

namespace RType::Network {
    /**
     * Abstract class for the network
     */
    template<typename ClientUDPSocket,
        typename ClientTCPSocket,
        typename IOService = _nullTemplate,
        typename Acceptor = _nullTemplate,
        typename SignalSet = _nullTemplate>
    class ANetwork : public INetwork {
        public:
        /**
         * Alias for std::shared_ptr<Client>
         */
        using client_shared_ptr = std::shared_ptr<AClient<ClientUDPSocket, ClientTCPSocket>>;
        /**
         * Get the list of all clients
         * @return A list of smart pointer of clients
         */
        virtual std::list<client_shared_ptr> GetClients() = 0;

        /**
         * Wait for a client and add it to the list of clients
         */
        virtual void wait_for_client() = 0;

        /**
         * Remove a client from the network
         */
        virtual void remove_client(AClient<ClientUDPSocket, ClientTCPSocket> *client) {
            auto it = std::find_if(this->_clients.begin(), this->_clients.end(),
                                   [&](const client_shared_ptr& registered_client) {
                                       if (registered_client.get() == client)
                                           printf(
                                               "[remove_client] Removing: %p\n",
                                               client);
                                       return (
                                           registered_client.get() == client
                                       );
                                   });
            if (it == std::end(this->_clients))
                throw std::exception();
            else
                this->_clients.erase(it);
        };

        protected:
        /**
         * Boolean corresponding to the network's state
         */
        bool _is_running = false;

        /**
         *List of shared pointer of clients
         */
        std::list<client_shared_ptr> _clients;
        /**
         * The mutex for the thread-safety for the list of clients
         */
        std::mutex _mutex;

        /**
         *
         */
        Router<IOService, Acceptor, SignalSet> _router;

        /**
         *
         */
        Room::RoomManager<ClientUDPSocket, ClientTCPSocket> _rooms;
    };


}

#endif
