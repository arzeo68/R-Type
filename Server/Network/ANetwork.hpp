/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ANETWORK_
#define SRC_RTYPE_ANETWORK_

#include <mutex>
#include <list>
#include "Router.hpp"
#include "INetwork.hpp"

namespace RType::Network {
    /**
     * Abstract class for the network
     */
    template<typename Client = _nullTemplate, typename IOService = _nullTemplate, typename Acceptor = _nullTemplate,
        typename SignalSet = _nullTemplate>
    class ANetwork : public INetwork<Client> {
        public:
        /**
         * Alias for std::shared_ptr<Client>
         */
        using client_shared_ptr = std::shared_ptr<Client>;
        /**
         * Get the list of all clients
         * @return A list of smart pointer of clients
         */
        virtual std::list<client_shared_ptr> GetClients() = 0;

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
    };


}

#endif
