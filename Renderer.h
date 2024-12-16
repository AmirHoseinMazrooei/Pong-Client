#pragma once
#include "Component.h"
#include "Transform.h"
#include <SDL.h>

class Renderer : public Component {
public:
    SDL_Color color;
    int width;
    int height;

    Renderer(SDL_Color col = { 255, 255, 255, 255 }, int w = 50, int h = 50)
        : color(col), width(w), height(h) {}

    void render(SDL_Renderer* renderer) override {
        if (!owner) return;

        Transform* transform = owner->getComponent<Transform>();
        if (transform) {
            SDL_Rect rect;
            rect.x = static_cast<int>(transform->position.x);
            rect.y = static_cast<int>(transform->position.y);
            rect.w = static_cast<int>(transform->scale.x * width);
            rect.h = static_cast<int>(transform->scale.y * height);

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};