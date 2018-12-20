#pragma once

#include "../../../common/math/vector/vector2f.h"

class GuiRect
{
  private:
  public:
    Vector2f pos;
    Vector2f size;
    operator float *() { return (float *)pos; }
    operator const float *() const { return (const float *)pos; }
    GuiRect() {}
    GuiRect(Vector2f pos, Vector2f size)
    {
        this->pos = pos;
        this->size = size;
    }
    GuiRect(float px, float py, float sx, float sy)
    {
        this->pos = Vector2f(px, py);
        this->size = Vector2f(sx, sy);
    }
};