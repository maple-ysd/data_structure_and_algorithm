#ifndef WEIGHTEDDIGRAPH_H_
#define WEIGHTEDDIGRAPH_H_

#include "DirectedEdge.h"
#include <iostream>
#include <vector>

class WeightedDigraph
{
public:
    WeightedDigraph(int N): vexNum(N), edgeNum(0), adjacent(vexNum) {}
    WeightedDigraph(std::istream &is);
    void addEdge(DirectedEdge e);
    std::vector<DirectedEdge> edges();
    std::vector<DirectedEdge> adj(int v) { return adjacent[v]; }
    int V() { return vexNum; }
    int E() { return edgeNum; }
    int outdegree(int v) { return adjacent[v].size(); }

    WeightedDigraph reverse();
    void print();
private:
    int vexNum;
    int edgeNum;
    std::vector<std::vector<DirectedEdge>> adjacent;
};

#endif // WEIGHTEDDIGRAPH_H_
