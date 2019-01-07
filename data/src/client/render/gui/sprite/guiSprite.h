#include "../baseGui.h"

class GuiSprite
{
private:
  GLuint vao;
  GLuint texId;
  Vector2f surfaceSize;
  Touple2f spriteMaxNum;
  GLuint vertexBufferObject;
  GLuint uvBufferObject;
  GLuint indexBufferObject;

public:
  GuiSprite();
  GuiSprite(GLuint texId);
  void setSurfaceSize(Vector2f surfaceSize);
  void setSpriteNum(Touple2f spriteMaxNum);
  void draw(const unsigned int spriteNum);
};