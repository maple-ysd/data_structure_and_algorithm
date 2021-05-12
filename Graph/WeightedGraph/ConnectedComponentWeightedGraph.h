#ifndef CONNECTEDCOMPONENTWEIGHTEDGRAPH_H_
#define CONNECTEDCOMPONENTWEIGHTEDGRAPH_H_

#include "WeightedGraph.h"

class ConnectedComponentWeightedGraph
{
public:
    ConnectedComponentWeightedGraph(WeightedGraph &wg);
    ~ConnectedComponentWeightedGraph() { delete[] visited; delete[] id; }
    bool connected(int vex1, int vex2) { return id[vex1] == id[vex2]; }
    int count() { return cnt; }
private:
    void dfs(WeightedGraph &wg, int origin, int v);
    bool *visited;
    int *id;
    int cnt;
};

#endif // CONNECTEDCOMPONENTWEIGHTEDGRAPH_H_
