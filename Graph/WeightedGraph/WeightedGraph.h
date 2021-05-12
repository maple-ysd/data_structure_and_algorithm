#ifndef WEIGHTEDGRAPH_H_
#define WEIGHTEDGRAPH_H_

#include "Edge.h"
#include <iostream>
#include <vector>

class WeightedGraph
{
public:
    WeightedGraph(int vertices): vexNum(vertices), edgeNum(0), adjacent(std::vector<std::vector<Edge*>>(vexNum)) {}
    WeightedGraph(std::istream &is);
    ~WeightedGraph();
    int E() { return edgeNum; }
    int V() { return vexNum; }
    std::vector<Edge*> adj(int vex) { return adjacent[vex]; }
    std::vector<Edge*> allEdges();
    void addEdge(Edge *e);
    void print();
private:
    int vexNum;
    int edgeNum;
    std::vector<std::vector<Edge*>> adjacent;        // 里面的vector<Edge*>代表邻接边的链表
};


#endif // WEIGHTEDGRAPH_H_
