#pragma once

class GameObject; // Forward declaration

class Component {
public:
    GameObject* owner = nullptr;

    virtual ~Component() = default;

    virtual void update() {}
    //virtual void render(SDL_Renderer* renderer) {}
};