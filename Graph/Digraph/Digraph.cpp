#include "Digraph.h"
#include <cstdlib>

Digraph::Digraph(int vertices): vexNum(vertices), edgeNum(0)
{
    adj = new SingleList<int>[vexNum];
    if (adj == nullptr)
    {
        std::cerr << "memory allocation failed in Digraph()\n";
        std::exit(EXIT_FAILURE);
    }
}

Digraph::Digraph(std::istream &is)
{
    is >> vexNum >> edgeNum;
    adj = new SingleList<int>[vexNum];
    if (adj == nullptr)
    {
        std::cerr << "memory allocation failed in Digraph()\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < edgeNum; ++i)
    {
        int vex1, vex2;
        is >> vex1 >> vex2;
        adj[vex1].add(vex2);
    }
}

void Digraph::addEdge(int vex1, int vex2)
{
    adj[vex1].add(vex2);
    ++edgeNum;
}

Digraph *Digraph::reverse()
{
    Digraph *temp = new Digraph(vexNum);
    for (int v = 0; v < vexNum; ++v)
        for (auto x : adj[v])
            temp->addEdge(x, v);
    return temp;
}

void Digraph::print()
{
    for (int v = 0; v < vexNum; ++v)
    {
        std::cout << v << ": ";
        for (auto x : adj[v])
            std::cout << x << " ";
        std::cout << std::endl;
    }
}
