#include "./guiImage.h"
GuiImage::GuiImage()
{
}
GuiImage::GuiImage(GLuint texId) : BaseGui(texId)
{
}
GuiImage::GuiImage(GLuint texId, Vector2f textureSize) : BaseGui(texId, textureSize)
{
}