#include "xMesh.h"
#include <fstream>

class XNode
{
private:
public:
  XNode();
  XNode(std::string frameName);

  XNode *node;
  XNode *next;
  std::string frameName;
  XMesh mesh;
};