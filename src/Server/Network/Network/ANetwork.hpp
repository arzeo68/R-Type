/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** ANetwork class implementation
*/

#ifndef SRC_RTYPE_ANETWORK_HPP_
#define SRC_RTYPE_ANETWORK_HPP_

#include <mutex>
#include <list>
#include <memory>
#include <algorithm>
#include "INetwork.hpp"
#include "Router.hpp"
#include "../Room/RoomManager.hpp"

namespace RType::Network {
    /**
     * Abstract class for the network. The class implements INetwork.
     * See INetwork for more explanations about the concept of Network
     * @tparam ClientUDPSocket UDP Socket type for the client
     * @tparam ClientTCPSocket TCP Socket type for the client
     * @tparam IOService See Router documentation
     * @tparam Acceptor See Router documentation
     * @tparam SignalSet See Router documentation
     */
    template<typename ClientUDPSocket,
        typename ClientTCPSocket,
        typename IOService = _nullTemplate,
        typename Acceptor = _nullTemplate,
        typename SignalSet = _nullTemplate>
    class ANetwork : public INetwork {
        public:
        /**
         * Alias for std::shared_ptr<AClient<...>>
         */
        using client_shared_ptr = std::shared_ptr<AClient<ClientUDPSocket, ClientTCPSocket>>;
        /**
         * Get the list of all clients
         * @return A list of shared pointer of AClient<...>
         */
        virtual std::list<client_shared_ptr> GetClients() = 0;
        /**
         * Wait for a client and add it to the list of clients. The function MAY accept further incoming connection
         */
        virtual void wait_for_client() = 0;

        /**
         * Remove a client from the list of clients. It takes a pointer to as generic as possible.
         * This a basic implementation but MAY be override for a custom implementation
         * @param client The client to be removed from the list
         */
        virtual void
        remove_client(AClient<ClientUDPSocket, ClientTCPSocket> *client) {
            std::lock_guard<std::mutex> lock(this->_mutex);
            auto it = std::find_if(this->_clients.begin(), this->_clients.end(),
                                   [&](const client_shared_ptr& registered_client) {
                                       return (
                                           registered_client.get() == client
                                       );
                                   });
            if (it != std::end(this->_clients))
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
         * The mutex for the thread-safety of the list of clients
         */
        std::mutex _mutex;

        /**
         * Explicit, see the class Router for further details
         */
        Router<IOService, Acceptor, SignalSet> _router;

        /**
         * Explicit, see the class RoomManager for further details
         */
        Room::RoomManager<ClientUDPSocket, ClientTCPSocket> _rooms;
    };


}

#endif
