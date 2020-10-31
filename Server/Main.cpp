/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <cstdio>
#include "Server/Network/BoostNetwork.hpp"

int main(int, char **) {
    RType::Network::BoostNetwork network(4242);
    network.run();
    //network.stop();
    //printf("Version: %li\n", __cplusplus);
    return (0);
}
