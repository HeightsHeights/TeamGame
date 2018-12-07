#include "xModel.h"
#include <vector>
#include "../../../common/math/vector/vectorSet.h"
#include "../../../common/loader/baseLoader.h"

class XLoader : public BaseLoader
{
private:
  int hierarchy;
  XModel *ret;
  int back;

  std::vector<Vector3f> vertices;
  std::vector<Vector2f> textures;
  std::vector<Vector3f> normals;

  std::vector<unsigned int> vertexIndices;
  std::vector<unsigned int> textureIndices;
  std::vector<unsigned int> normalIndices;

  void readMesh(XNode *node);
  void readFrame(XNode *node);
  bool virtual readFile();

public:
  XModel *load(const std::string dirPath, const std::string fileName);
};