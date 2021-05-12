#include "Edge.h"

bool cmp(Edge* lhs, Edge *rhs)  // 用于建造小顶堆
{
    return lhs->weight > rhs->weight;
}
