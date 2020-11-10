/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "Network.hpp"

RType::Common::Network::TCPPacket RType::Common::Network::packet_unpack(const std::string& str) {
    return *(struct Common::Network::TCPPacket *) str.data();
}
