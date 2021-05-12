#include "AcyclicLP.h"
#include "Topological.h"

AcyclicLP::AcyclicLP(WeightedDigraph &g, int s): edgeTo(g.V()), distTo(g.V())
{
    for (int i = 0; i < g.V(); ++i)
        distTo[i] = Min_Weight;
    distTo[s] = 0.0;

    Topological topo(g);
    for (auto v : topo.order())
        relax(g, v);
    std::cout << distTo[0] << std::endl;
}

void AcyclicLP::relax(WeightedDigraph &g, int v)
{
    for (auto e : g.adj(v))
    {
        int w = e.to();
        if (distTo[w] < distTo[v] + e.getWeight())
        {
            distTo[w] = distTo[v] + e.getWeight();
            edgeTo[w] = e;
        }
    }
}

std::stack<DirectedEdge> AcyclicLP::pathTo(int v)
{
    std::stack<DirectedEdge> s;
    if (hasPathTo(v))
    {
        while (distTo[v] != 0.0)
        {
            s.push(edgeTo[v]);
            v = edgeTo[v].from();
        }
    }
        return s;
}
