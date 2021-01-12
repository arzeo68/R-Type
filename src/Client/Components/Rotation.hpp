#pragma once

struct RotationComponent {
public:
    RotationComponent() = default;
    RotationComponent(float rate) : rate(rate) { }

    float rate;
};