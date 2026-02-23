/* Copyright (c) 2026. LetTheMiceFree. */

#ifndef ENTITY_MODULE_H
#define ENTITY_MODULE_H

#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include <SDL3/SDL.h>

#include "component.h"

class GameApp;

class Entity
{
public:
    bool Alive = true;

    Entity() = default;
    virtual ~Entity() = default;

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *ptr;
        Components.push_back(std::move(ptr));
        return ref;
    }

    template <typename T>
    T* GetComponent()
    {
        for (auto& c : Components)
        {
            if (auto casted = dynamic_cast<T*>(c.get()))
                return casted;
        }
        return nullptr;
    }

    void HandleEvent(GameApp& app, const SDL_Event& e)
    {
        for (auto& c : Components)
            c->HandleEvent(app, *this, e);
    }

    void Update(GameApp& app, float dt)
    {
        for (auto& c : Components)
            c->Update(app, *this, dt);
    }

    void Draw(SDL_Renderer* renderer)
    {
        for (auto& c : Components)
            c->Draw(*this, renderer);
    }

private:
    std::vector<std::unique_ptr<Component>> Components;
};


#endif /* ENTITY_MODULE_H */
