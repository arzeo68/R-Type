#pragma once

#include <string>

namespace RType
{

struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(std::string const& tag) : tag(tag) { };
};

} // namespace RType
