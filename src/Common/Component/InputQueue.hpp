#pragma once

#include <deque>
#include <unordered_map>
#include <utility>
#include <Common/ECS/World.hpp>

namespace RType {

struct InputQueueComponent {
    std::unordered_map<int, std::deque<int>> InputQueueMap;

    InputQueueComponent() = default;
};

}