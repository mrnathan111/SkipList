#include "sNode.h"

sNode::sNode(int d)
{
    data = d;
    next = nullptr;
    prev = nullptr;
    upLevel = nullptr;
    downLevel = nullptr;
}
