//
// Created by yifan on 2/23/2026.
//

#ifndef INC_420J12_DRAG_COMPONENT_H
#define INC_420J12_DRAG_COMPONENT_H
#include <memory>
#include <SDL3/SDL.h>

#include "component.h"
#include "entity.h"
#include "render_component.h"
#include "drag_state.h"
#include "token.h"
#include "bag.h"
#include "game_state.h"

// 小工具：点是否在矩形内
inline bool PointInRect(float px, float py, const SDL_FRect& r)
{
    return px >= r.x && px <= (r.x + r.w) && py >= r.y && py <= (r.y + r.h);
}
//Q5
inline bool Intersects(const SDL_FRect& a, const SDL_FRect& b)
{
    const float aRight = a.x + a.w;
    const float aBottom = a.y + a.h;
    const float bRight = b.x + b.w;
    const float bBottom = b.y + b.h;

    return (a.x < bRight) && (aRight > b.x) && (a.y < bBottom) && (aBottom > b.y);
}

class DragComponent final : public Component
{
public:
    bool Dragging = false;
    float OffsetX = 0.f;
    float OffsetY = 0.f;
    std::unique_ptr<DragState> State = std::make_unique<NotSelectedState>();

    void HandleEvent(GameApp& app, Entity& owner, const SDL_Event& e) override
    {
        auto* tr = owner.GetComponent<TransformComponent>();
        if (!tr) return;

        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            float mx = static_cast<float>(e.button.x);
            float my = static_cast<float>(e.button.y);

            if (PointInRect(mx, my, tr->Rect))
            {
                // 进入拖拽：记录鼠标点相对矩形左上角的偏移
                Dragging = true;
                OffsetX = mx - tr->Rect.x;
                OffsetY = my - tr->Rect.y;

                State = std::make_unique<ClickedState>();
            }
        }
        else if (e.type == SDL_EVENT_MOUSE_MOTION)
        {
            if (Dragging)
            {
                float mx = static_cast<float>(e.motion.x);
                float my = static_cast<float>(e.motion.y);

                tr->Rect.x = mx - OffsetX;
                tr->Rect.y = my - OffsetY;
            }
        }
        else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && e.button.button == SDL_BUTTON_LEFT)
        {
            if (Dragging)
            {
                Dragging = false;
                State = std::make_unique<NotSelectedState>();

                // ===== Q5: Collect if dropped on Bag =====
                if (GameState::BagPtr != nullptr)
                {
                    auto* bagTr = GameState::BagPtr->GetComponent<TransformComponent>();
                    auto* myTr  = owner.GetComponent<TransformComponent>();

                    if (bagTr && myTr && Intersects(myTr->Rect, bagTr->Rect))
                    {
                        // owner 必须是 Token 才能加分
                        if (auto* tok = dynamic_cast<Token*>(&owner))
                        {
                            GameState::BagPtr->AddScore(tok->GetPoints());
                            owner.Alive = false; // 不画即可（简单稳）
                        }
                    }
                }
            }
        }
    }
    void Update(GameApp& app, Entity& owner, float dt) override
    {
        auto* rend = owner.GetComponent<RectangleRenderComponent>();
        if (!rend) return;

        rend->DrawOutline = true;
        rend->Outline = State->OutlineColor();
    }
};
#endif //INC_420J12_DRAG_COMPONENT_H