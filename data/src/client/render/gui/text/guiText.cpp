#include "./guiText.h"
GuiText::GuiText()
{
}
GuiText::GuiText(GLuint texId) : BaseGui(texId)
{
}
GuiText::GuiText(GLuint texId, Vector2f textureSize) : BaseGui(texId, textureSize)
{
}
GuiText::~GuiText()
{
}