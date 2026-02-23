//
// Created by yifan on 2/23/2026.
//

#ifndef INC_420J12_BAG_H
#define INC_420J12_BAG_H
#include <SDL3/SDL.h>
#include "entity.h"
#include "render_component.h"

class Bag final : public Entity
{
public:
    int Score = 0;
    void AddScore(int v) { Score += v; }
};
#endif //INC_420J12_BAG_H