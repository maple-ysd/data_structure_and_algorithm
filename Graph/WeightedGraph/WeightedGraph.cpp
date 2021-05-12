#include "WeightedGraph.h"

WeightedGraph::WeightedGraph(std::istream &is)
{
    int n;
    is >> vexNum >> n;
    adjacent = std::vector<std::vector<Edge*>>(vexNum);
    int vex1, vex2;
    double w;
    for (int i = 0; i< n; ++i)
    {
        is >> vex1 >> vex2 >> w;
        Edge* e = new Edge(vex1, vex2, w);
        addEdge(e);
    }
}

WeightedGraph::~WeightedGraph()
{
    for (auto e : allEdges())
        delete e;
}

std::vector<Edge*> WeightedGraph::allEdges()
{
    std::vector<Edge*> v;
    for (int i = 0; i < vexNum; ++i)
    {
        int sz = adjacent[i].size();
        for (int j = 0; j < sz; ++j)
        {
            int w = adjacent[i][j]->other(i);
            if (i < w) v.push_back(adjacent[i][j]);
        }
    }
    return v;
}

void WeightedGraph::addEdge(Edge *e)
{
    int vex1 = e->either();
    int vex2 = e->other(vex1);
    adjacent[vex1].push_back(e);
    adjacent[vex2].push_back(e);
    ++edgeNum;
}

void WeightedGraph::print()
{
    for (auto &v : adjacent)
    {
        for (auto e : v)
            e->print();
        std::cout << std::endl;
    }
}
