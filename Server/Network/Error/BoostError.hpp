/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_NETWORK_BOOST_ERROR
#define SRC_NETWORK_BOOST_ERROR

#include "Error.hpp"


namespace RType::Network {
    class BoostError : Error<boost::system::error_code> {

    };
}

#endif
