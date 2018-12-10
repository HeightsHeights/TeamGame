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
  unsigned int getFilePos();
  void jumpFile(unsigned int pos);

  bool loadFile(const char *filePath);
};