#include "testXModel.h"
#include <vector>
#include "../../../common/math/vector/vectorSet.h"
#include "../../common/loader/baseLoader.h"

class TestXLoader : public BaseLoader
{
private:
  int hierarchy;
  TestXModel *ret;
  int back;

  std::vector<Vector3f> vertices;
  std::vector<Vector2f> textures;
  std::vector<Vector3f> normals;

  std::vector<unsigned int> vertexIndices;
  std::vector<unsigned int> textureIndices;
  std::vector<unsigned int> normalIndices;

  void readMesh(TestXNode *node);
  void readFrame(TestXNode *node);
  bool virtual readFile();

public:
  TestXModel *load(const std::string dirPath, const std::string fileName);
};