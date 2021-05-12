#ifndef CYCLEFINDER_H_
#define CYCLEFINDER_H_

#include "WeightedDigraph.h"
#include <stack>

class CycleFinder
{
public:
    CycleFinder(WeightedDigraph &g);
    std::stack<DirectedEdge> getCycle() { return cycle; }
    bool hasCycle() { return cycleFound; }
private:
    void dfs(WeightedDigraph &g, int v);
    std::vector<bool> visited;
    std::vector<DirectedEdge> edgeTo;
    std::vector<bool> onStack;
    std::stack<DirectedEdge> cycle;
    bool cycleFound;
};

#endif // CYCLEFINDER_H_
