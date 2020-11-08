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
    class INetwork {
        public:
        virtual ~INetwork() = default;

        virtual void pre_run() = 0;

        /**
         * run the network. This function might add client
         */
        virtual void run() = 0;

        /**
         * Stop the network
         */
        virtual void stop() = 0;
    };
}

#endif
