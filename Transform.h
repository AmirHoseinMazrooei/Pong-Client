#pragma once
#include "Component.h"
struct Vector2 {
    float x;
    float y;
};

class Transform : public Component {
public:
    Vector2 position;
    float rotation;
    Vector2 scale;

    Transform(float x = 0.0f, float y = 0.0f, float rot = 0.0f, float sx = 1.0f, float sy = 1.0f)
        : position{ x, y }, rotation(rot), scale{ sx, sy } {}

    void update() override {
        // Implement transformation logic if needed
    }
};