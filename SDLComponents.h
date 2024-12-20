#pragma once
#include <iostream>
#include "IRenderer.h"
#include "SDL.h"
#include <string>

class SDLRectRenderer : public IRenderer {
public:
	SDLRectRenderer(SDL_Renderer* renderer) : sdlRenderer(renderer) {}

	void Draw() override {
		Transform* transform = owner->getComponent<Transform>();
		SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);


		DrawRectangle(static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), static_cast<int>(transform->scale.x), static_cast<int>(transform->scale.y)); // Default size 50x30
	}


private:
	SDL_Renderer* sdlRenderer;


	void DrawRectangle(int x, int y, int width, int height) {
		SDL_Rect rect = { x - width / 2, y - height / 2, width, height };
		//draw a filled rectangle
		SDL_RenderFillRect(sdlRenderer, &rect);
	}
};
class SDLCircleRenderer : public IRenderer {
public:
	SDLCircleRenderer(SDL_Renderer* renderer) : sdlRenderer(renderer) {}
	void Draw() override {
		Transform* transform = owner->getComponent<Transform>();
		SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);


		// Determine shape and render
		DrawFilledCircle(static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), static_cast<int>(transform->scale.y)); // Default radius 30
	}
private:
	SDL_Renderer* sdlRenderer;

    void DrawFilledCircle(int x0, int y0, int radius) {
        int x = radius;
        int y = 0;
        int radiusError = 1 - x;

        while (x >= y) {
            // Draw horizontal lines between the points to fill the circle
            SDL_RenderDrawLine(sdlRenderer, x0 - x, y0 + y, x0 + x, y0 + y);
            SDL_RenderDrawLine(sdlRenderer, x0 - y, y0 + x, x0 + y, y0 + x);
            SDL_RenderDrawLine(sdlRenderer, x0 - x, y0 - y, x0 + x, y0 - y);
            SDL_RenderDrawLine(sdlRenderer, x0 - y, y0 - x, x0 + y, y0 - x);

            y++;
            if (radiusError < 0) {
                radiusError += 2 * y + 1;
            } else {
                x--;
                radiusError += 2 * (y - x) + 1;
            }
        }
    }
};
