#include "testXMesh.h"
#include <fstream>

class TestXNode
{
  private:
  public:
    TestXNode *node;
    TestXNode *next;
    std::string frameName;
    TestXMesh mesh;
};