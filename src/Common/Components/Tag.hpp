#pragma once

#include <string>

struct TagComponent {
    TagComponent() = default;
    TagComponent(const std::string& s) : tag(s) {};
    std::string tag;
};
