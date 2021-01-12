#pragma once

#include <cstdint>
#include <bitset>

namespace ECS
{

typedef uint32_t Entity;
static const Entity MAX_ENTITIES = 20000;

typedef uint16_t ComponentType;
static const ComponentType MAX_COMPONENTS = 64;

typedef std::bitset<MAX_COMPONENTS> Signature;

} // namespace ECS