//
// Created by yifan on 2/23/2026.
//

#ifndef INC_420J12_COMPONENT_H
#define INC_420J12_COMPONENT_H

#include <SDL3/SDL.h>

class GameApp;
class Entity;

class Component
{
public:
    virtual ~Component() = default;

    virtual void HandleEvent(GameApp& app, Entity& owner, const SDL_Event& e) {}
    virtual void Update(GameApp& app, Entity& owner, float dt) {}
    virtual void Draw(GameApp& app, Entity& owner) {}
};

#endif //INC_420J12_COMPONENT_H