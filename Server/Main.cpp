/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Server/Network/NetworkBoost.hpp"

class Test {
    public:
    Test() = default;
};

int main(int, char **) {
    RType::Network::NetworkBoost network(4242);
    network.run();
    network.stop();
    return (0);
}
