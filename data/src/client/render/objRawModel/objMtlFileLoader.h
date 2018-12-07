#pragma once
#include "./objRawModel.h"
#include "./objTextureLoader.h"
#include "../../../common/loader/baseLoader.h"
class ObjMtlFileLoader : public BaseLoader
{
private:
  ObjRawModel *model;
  ObjTextureLoader texLoader;

  virtual bool readFile();
  void createMaterial();

public:
  ObjMtlFileLoader(ObjRawModel *model, std::string dirPath);
  bool load(const char *filePath);
};