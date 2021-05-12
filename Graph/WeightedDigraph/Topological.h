#ifndef TOPOLOGICAL_H_
#define TOPOLOGICAL_H_

#include "WeightedDigraph.h"
#include <queue>
#include <vector>

class Topological
{
public:
    Topological(WeightedDigraph &g);
    std::vector<int> order() { return topoOrder; }
private:
    std::vector<int> indegrees;
    std::vector<int> topoOrder;
};

#endif // TOPOLOGICAL_H_
