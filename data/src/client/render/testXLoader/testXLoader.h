#include "testXModel.h"
#include <vector>
#include "../../../common/math/vector/vectorSet.h"

class TestXLoader
{
private:
  int hierarchy;
  TestXModel *ret;
  std::ifstream file;
  int back;

  std::vector<Vector3f> vertices;
  std::vector<Vector2f> textures;
  std::vector<Vector3f> normals;

  std::vector<unsigned int> vertexIndices;
  std::vector<unsigned int> textureIndices;
  std::vector<unsigned int> normalIndices;

  void skipLine();
  void skip2Key(const char key);

  void readMesh(TestXNode *node);
  void readFrame(TestXNode *node);
  void readXFile();

  bool loadXFile(const char *filePath);

public:
  TestXModel *load(const std::string dirPath, const std::string fileName);
};