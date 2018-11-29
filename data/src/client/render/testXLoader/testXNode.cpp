#include "testXNode.h"
TestXNode::TestXNode()
{
    this->node = NULL;
    this->next = NULL;
}
TestXNode::TestXNode(std::string frameName)
{
    this->node = NULL;
    this->next = NULL;
    this->frameName = frameName;
}