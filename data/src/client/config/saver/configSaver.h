#pragma once

#include "../../../common/saver/baseSaver.h"
#include "../configData.h"

class ConfigSaver : public BaseSaver
{
private:
  ConfigData *data;
  virtual bool writeFile();

public:
  ConfigSaver() : BaseSaver() {}
  bool save(std::string fileNamen, ConfigData *data);
};