#include "testXMesh.h"
#include <fstream>

class TestXNode
{
private:
public:
  TestXNode();

  TestXNode *node;
  TestXNode *next;
  std::string frameName;
  TestXMesh mesh;
};