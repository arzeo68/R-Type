#pragma once

#include <vector>

namespace ECS
{

#pragma pack(push, 1)
struct NetworkPacket {
    int id;
    int type;
    float x, y;
};
#pragma pack(pop)

} // namespace ECS
