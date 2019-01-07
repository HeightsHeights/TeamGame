#include "../baseGui.h"

class GuiSprite : public BaseGui
{
private:
  Vector2f surfaceSize;
  Touple2f spriteNum;

public:
  GuiSprite();
  GuiSprite(GLuint texId);
  void setSurfaceSize(Vector2f surfaceSize);
  void setSpriteNum(Touple2f spriteNum);
  void draw(const unsigned int spriteNum);
};