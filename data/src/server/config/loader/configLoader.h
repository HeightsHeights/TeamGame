#pragma once

#include "../../../common/loader/baseLoader.h"
#include "../configData.h"

class ConfigLoader : public BaseLoader
{
private:
  ConfigData *ret;
  virtual bool readFile();

public:
  ConfigLoader() : BaseLoader() {}
  ConfigData *load(std::string fileName);
};