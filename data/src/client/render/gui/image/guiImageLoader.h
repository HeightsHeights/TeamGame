#pragma once

#include "../baseGuiLoader.h"
#include "./guiImage.h"

class GuiImageLoader : public BaseGuiLoader
{
private:
public:
  GuiImageLoader();
  GuiImage *load(const char *filePath);
};