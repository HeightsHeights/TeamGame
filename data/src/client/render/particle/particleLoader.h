#pragma once

#include "./particle.h"
#include "../gui/baseGuiLoader.h"

class ParticleLoader : public BaseGuiLoader
{
private:
  Particle *ret;

public:
  ParticleLoader();
  Particle *load(const char *filePath, const unsigned int horizontallyNum, const unsigned int verticallyNum);
};