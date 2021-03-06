#pragma once

#include <iostream>
#include <Client/typeEncapsulation.hpp>

namespace RType
{

struct TransformComponent {
public:
    TransformComponent() = default;

    TransformComponent(vec2f position, float angle, vec2f scale)
        : position(position), angle(angle), scale(scale)
    { }

    vec2f position;
    float angle;
    vec2f scale;
};

[[maybe_unused]] static std::ostream& operator<<(std::ostream& out, TransformComponent const& t)
{
    out << "TransformComponent : { position : ( " << t.position.x << ", " << t.position.y << " ), rotation : " << t.angle << ", scale : ( " << t.scale.x << ", " << t.scale.y << " ) }";
    return out;
}

} // namespace RType
