#pragma once

#include <string>

namespace Rtype
{

struct TagComponent {
    std::string tag;

    TagComponent() = default;
    TagComponent(std::string const& tag) : tag(tag) { };
};

} // namespace Rtype
