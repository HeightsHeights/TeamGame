#pragma once

#include <fstream>

class BaseLoader
{
private:
  virtual bool readFile() {}

public:
  BaseLoader() {}

protected:
  std::ifstream file;

  void skipLine();
  void skip2Key(const char key);

  bool loadFile(const char *filePath);
};