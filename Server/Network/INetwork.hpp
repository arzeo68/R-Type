/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_RTYPE_INETWORK_
#define SRC_RTYPE_INETWORK_

#include <memory>

namespace RType::Network {

    /**
     * Interface for the network. Defining the fundamental functions
     */
    template<typename Client = _nullTemplate>
    class INetwork {
        public:
        virtual ~INetwork() = default;
        /**
         * Run the network. This function might add client
         */
        virtual void run() = 0;

        /**
         * Stop the network
         */
        virtual void stop() = 0;

        /**
         * Remove a client from the network
         */
        //virtual typename std::enable_if_t<!std::is_same_v<Socket, _TemplateNull>>
        virtual void add_client(Client &&) = 0;

        /**
         * Remove a client from the network
         */
        //virtual typename std::enable_if_t<!std::is_base_of_v<Socket, _TemplateNull>>
        virtual void remove_client(Client &&) = 0;
    };
}

#endif
