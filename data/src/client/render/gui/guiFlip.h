#pragma once

class GuiFlip
{
  private:
  public:
    bool x;
    bool y;
    bool z;
    GuiFlip() { x = y = z = false; }
    GuiFlip(bool x, bool y, bool z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};