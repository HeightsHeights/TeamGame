#include "../baseGui.h"

class GuiImage : public BaseGui
{
private:
public:
  GuiImage();
  GuiImage(GLuint texId);
  GuiImage(GLuint texId, Vector2f textureSize);
};