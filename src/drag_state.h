//
// Created by yifan on 2/23/2026.
//

#ifndef INC_420J12_DRAG_STATE_H
#define INC_420J12_DRAG_STATE_H
#include <SDL3/SDL.h>

class DragState
{
public:
    virtual ~DragState() = default;
    virtual SDL_Color OutlineColor() const = 0;
};

class NotSelectedState final : public DragState
{
public:
    SDL_Color OutlineColor() const override { return SDL_Color{0, 0, 0, 0}; } // 不画描边
};

class SelectedState final : public DragState
{
public:
    SDL_Color OutlineColor() const override { return SDL_Color{255, 255, 255, 255}; } // 白色描边
};

class ClickedState final : public DragState
{
public:
    SDL_Color OutlineColor() const override { return SDL_Color{255, 220, 120, 255}; } // 黄描边（先占位）
};
#endif //INC_420J12_DRAG_STATE_H