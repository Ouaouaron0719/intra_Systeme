//
// Created by yifan on 2/23/2026.
//

#ifndef INC_420J12_TOKEN_H
#define INC_420J12_TOKEN_H
#include <memory>
#include <SDL3/SDL.h>
#include "entity.h"
#include "render_component.h" // 你 Q2 的 TransformComponent / RectangleRenderComponent

// ====== Point State Pattern ======
class TokenPointState
{
public:
    virtual ~TokenPointState() = default;
    virtual int Points() const = 0;
    virtual SDL_Color Color() const = 0; // 方便 Q3 直接用不同颜色看出来
};

class NormalTokenState final : public TokenPointState
{
public:
    int Points() const override { return 1; }
    SDL_Color Color() const override { return SDL_Color{80, 200, 120, 255}; }
};

class SuperTokenState final : public TokenPointState
{
public:
    int Points() const override { return 3; }
    SDL_Color Color() const override { return SDL_Color{80, 160, 240, 255}; }
};

class OmegaTokenState final : public TokenPointState
{
public:
    int Points() const override { return 10; }
    SDL_Color Color() const override { return SDL_Color{240, 120, 80, 255}; }
};

// ====== Token Entity ======
class Token final : public Entity
{
public:
    std::unique_ptr<TokenPointState> PointState;

    explicit Token(std::unique_ptr<TokenPointState> state)
        : PointState(std::move(state))
    {}

    int GetPoints() const { return PointState ? PointState->Points() : 0; }
};
#endif //INC_420J12_TOKEN_H