//
// Created by yifan on 2/23/2026.
//
#include "render_component.h"

// Draw 需要：Renderer + Transform
void RectangleRenderComponent::Draw(Entity& owner, SDL_Renderer* renderer)
{
    auto* tr = owner.GetComponent<TransformComponent>();
    if (!tr) return;

    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);

    if (Filled)
        SDL_RenderFillRect(renderer, &tr->Rect);
    else
        SDL_RenderRect(renderer, &tr->Rect);
}