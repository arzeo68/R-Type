/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_RTYPE_COMMON_NETWORK
#define SRC_RTYPE_COMMON_NETWORK

#include <string>
#include <cstdint>

namespace RType::Common::Network {
    static const constexpr uint16_t g_MagicNumber = 0x10FCu;
    const static constexpr uint16_t g_maxMessageLength = 256u;

    #pragma pack(push, 1)
    struct TCPPacket {
        uint16_t magic;
        char message[g_maxMessageLength];
    };
    #pragma pack(pop)
    TCPPacket packet_unpack(const std::string& data);
}

#endif
