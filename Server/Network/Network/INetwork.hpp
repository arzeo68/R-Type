/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** INetwork class implementation
*/

#ifndef SRC_RTYPE_INETWORK_
#define SRC_RTYPE_INETWORK_

namespace RType::Network {

    /**
     * Interface for the network. Defining the fundamental functions
     */
    class INetwork {
        public:
        virtual ~INetwork() = default;

        /**
         * A function that allows to pre_run things before the main run function.
         */
        virtual void pre_run() = 0;

        /**
         * Run the network
         */
        virtual void run() = 0;

        /**
         * Stop the network
         */
        virtual void stop() = 0;
    };
}

#endif
