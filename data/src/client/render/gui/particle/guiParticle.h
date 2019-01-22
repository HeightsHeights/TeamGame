#pragma once
#include "../baseGui.h"

class GuiParticle : public BaseGui
{
private:
public:
    GuiParticle();
    GuiParticle(GLuint texId);
    GuiParticle(GLuint texId, Vector2f textureSize);
    ~GuiParticle();
};