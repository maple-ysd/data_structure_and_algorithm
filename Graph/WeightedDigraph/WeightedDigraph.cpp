#include "WeightedDigraph.h"

WeightedDigraph::WeightedDigraph(std::istream &is)
{
    is >> vexNum >> edgeNum;
    adjacent = std::vector<std::vector<DirectedEdge>>(vexNum);

    for (int i = 0; i < edgeNum; ++i)
    {
        int vex1, vex2;
        double w;
        is >> vex1 >> vex2 >> w;
        adjacent[vex1].push_back(DirectedEdge(vex1, vex2, w));
    }
}

void WeightedDigraph::addEdge(DirectedEdge e)
{
    adjacent[e.from()].push_back(e);
    ++edgeNum;
}

std::vector<DirectedEdge> WeightedDigraph::edges()
{
    std::vector<DirectedEdge> v;
    for (int i = 0; i < vexNum; ++i)
        for (DirectedEdge e : adjacent[i])
            v.push_back(e);
    return v;
}

WeightedDigraph WeightedDigraph::reverse()
{
    WeightedDigraph ret(vexNum);
    for (int v = 0; v < vexNum; ++v)
    {
        for (auto e : adjacent[v])
            ret.addEdge(DirectedEdge(e.to(), e.from(), e.getWeight()));
    }
    return ret;
}

void WeightedDigraph::print()
{
    for (int v = 0; v < vexNum; ++v)
    {
        for (auto e : adjacent[v])
            e.print();
        std::cout << std::endl;
    }
}
