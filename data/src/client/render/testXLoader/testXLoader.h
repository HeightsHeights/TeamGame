#include "testXModel.h"

class TestXLoader
{
private:
  TestXModel *ret;
  std::ifstream file;

  bool loadXFile(const char *filePath);

public:
  TestXModel *load(const std::string dirPath, const std::string fileName);
};