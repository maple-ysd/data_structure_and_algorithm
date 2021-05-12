#include "AcyclicSP.h"
#include "Topological.h"

AcyclicSP::AcyclicSP(WeightedDigraph &g, int s): edgeTo(g.V()), distTo(g.V())
{
    for (int i = 0; i < g.V(); ++i)
        distTo[i] = DBL_MAX;
    distTo[s] = 0;

    Topological t(g);
    for (int v : t.order())
        relax(g, v);
}

void AcyclicSP::relax(WeightedDigraph &g, int v)
{
    for (auto e : g.adj(v))
    {
        int w = e.to();
        if (distTo[w] > distTo[v] + e.getWeight())
        {
            distTo[w] = distTo[v] + e.getWeight();
            edgeTo[w] = e;
        }
    }
}

std::stack<DirectedEdge> AcyclicSP::pathTo(int v)
{
    std::stack<DirectedEdge> s;
    if (hasPathTo(v))
    {
        while (distTo[v] != 0)
        {
            s.push(edgeTo[v]);
            v = edgeTo[v].from();
        }
    }
    return s;
}
