#include "xNode.h"
XNode::XNode()
{
    this->node = NULL;
    this->next = NULL;
}
XNode::XNode(std::string frameName)
{
    this->node = NULL;
    this->next = NULL;
    this->frameName = frameName;
}