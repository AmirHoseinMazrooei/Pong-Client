#pragma once
#include <vector>
#include <memory>
#include <type_traits>
#include "Component.h"
#include <string>
#include <SDL.h>
#include "Transform.h"
#include "IRenderer.h"

class GameObject {
public:
    std::string name;
    std::vector<std::unique_ptr<Component>> components;

    GameObject(const std::string& name_) : name(name_) {}

    template <typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = component.get();
        component->owner = this;
        components.emplace_back(std::move(component));
        return ptr;
    }

    template <typename T>
    T* getComponent() {
        for (auto& comp : components) {
            if (T* ptr = dynamic_cast<T*>(comp.get())) {
                return ptr;
            }
        }
        return nullptr;
    }

    void update() {
        for (auto& comp : components) {
            comp->update();
        }
    }

    void render() {
		if (auto renderer = getComponent<IRenderer>()) {
			renderer->Draw();
		}
    }
};