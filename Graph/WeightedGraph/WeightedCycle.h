#ifndef WEIGHTEDCYCLE_H_
#define WEIGHTEDCYCLE_H_

#include "WeightedGraph.h"
#include <stack>

class WeightedCycle
{
public:
    WeightedCycle(WeightedGraph &wg);
    ~WeightedCycle()
    {
        delete[] visited;
        delete[] edgeTo;
        delete[] onStack;
    }
    bool hasCycle() { return cycleFound; }
    std::stack<Edge*> getCycle() { return cycle; }
private:
    void dfs(WeightedGraph &wg, int origin, int vex);
    bool *visited;
    Edge **edgeTo;
    bool *onStack;
    std::stack<Edge*> cycle;
    bool cycleFound;

};

#endif // WEIGHTEDCYCLE_H_
