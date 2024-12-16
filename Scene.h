#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"

class Scene {
public:
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    GameObject* createGameObject(const std::string& name) {
        auto gameObject = std::make_unique<GameObject>(name);
        GameObject* ptr = gameObject.get();
        gameObjects.emplace_back(std::move(gameObject));
        return ptr;
    }

    void update() {
        for (auto& obj : gameObjects) {
            obj->update();
        }
    }

    void render(SDL_Renderer* renderer) {
        for (auto& obj : gameObjects) {
            obj->render(renderer);
        }
    }
};