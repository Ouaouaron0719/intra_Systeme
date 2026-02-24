//
// Created by yifan on 2/23/2026.
//

#ifndef INC_420J12_RENDER_COMPONENT_H
#define INC_420J12_RENDER_COMPONENT_H
#include <SDL3/SDL.h>
#include "component.h"
#include "entity.h"

// 负责位置和尺寸
class TransformComponent final : public Component
{
public:
    SDL_FRect Rect{0.f, 0.f, 10.f, 10.f};

    TransformComponent() = default;
    TransformComponent(float x, float y, float w, float h)
    {
        Rect.x = x;
        Rect.y = y;
        Rect.w = w;
        Rect.h = h;
    }
};

// 负责画矩形（颜色）
class RectangleRenderComponent final : public Component
{
public:
    SDL_Color Color{255, 255, 255, 255};
    bool Filled = true;

    SDL_Color Outline{0,0,0,0};
    bool DrawOutline = false;

    RectangleRenderComponent() = default;
    explicit RectangleRenderComponent(SDL_Color c, bool filled = true)
        : Color(c), Filled(filled) {}

    void Draw(Entity& owner, SDL_Renderer* renderer) override;
};
#endif //INC_420J12_RENDER_COMPONENT_H