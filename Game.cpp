#include <SDL.h>
#include <iostream>
#include "Scene.h"
#include "Transform.h"
#include "Renderer.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("GameObject System",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Scene scene;

    // Create Player GameObject
    GameObject* player = scene.createGameObject("Player");
    player->addComponent<Transform>(100.0f, 100.0f, 0.0f, 1.0f, 1.0f);
    player->addComponent<Renderer>(SDL_Color{ 255, 0, 0, 255 }, 50, 50);
    bool running = true;
    SDL_Event event;

    while (running) {
        // Event Handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
            // Additional event handling (e.g., input) can be added here
        }

        // Update Scene
        scene.update();

        // Render Scene
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        scene.render(renderer);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}