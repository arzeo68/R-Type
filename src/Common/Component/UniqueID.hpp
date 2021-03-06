#pragma once

#include <iostream>
#include <cstdint>

namespace RType
{

enum NetworkPacketType {
    NPT_CREATE,
    NPT_UPDATE,
    NPT_DESTROY
};

struct UniqueID {
    uint32_t id;

    UniqueID() = default;
    UniqueID(uint32_t id) : id(id) { }
};

} // namespace RType
