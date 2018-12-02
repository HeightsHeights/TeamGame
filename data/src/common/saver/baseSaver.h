#pragma once

#include <fstream>

class BaseSaver
{
private:
  virtual bool writeFile() {}

public:
  BaseSaver() {}

protected:
  std::ofstream file;

  bool saveFile(const char *filePath);
};