#pragma once

#include "../baseGui.h"

class GuiText : public BaseGui
{
private:
public:
  GuiText();
  GuiText(GLuint texId);
  GuiText(GLuint texId, Vector2f textureSize);
  ~GuiText();
};