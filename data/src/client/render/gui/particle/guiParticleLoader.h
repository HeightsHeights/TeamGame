#pragma once

#include "../baseGuiLoader.h"
#include "./guiParticle.h"

class GuiParticleLoader : public BaseGuiLoader
{
private:
public:
  GuiParticleLoader();
  GuiParticle *load(const char *filePath, unsigned int count);
};