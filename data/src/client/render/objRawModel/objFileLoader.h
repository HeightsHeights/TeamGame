#pragma once
#include "./objRawModel.h"

#include "../../../common/loader/baseLoader.h"
#include "../../../common/math/vector/vectorSet.h"

#include <vector>

class ObjFileLoader : public BaseLoader
{
private:
  std::vector<Vector3f> vertices;
  std::vector<Vector2f> textures;
  std::vector<Vector3f> normals;

  std::vector<unsigned int> vertexIndices;
  std::vector<unsigned int> textureIndices;
  std::vector<unsigned int> normalIndices;

  ObjRawModel *model;

  virtual bool readFile();
  void createSubset();
  void processVertex(unsigned int textureIndexArray[], Vector2f uvArray[], Vector3f normalSumArray[]);

public:
  ObjFileLoader(ObjRawModel *model) { this->model = model; }
  bool load(const char *filePath);
};