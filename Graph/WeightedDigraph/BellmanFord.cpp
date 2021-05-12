#include "BellmanFordSP.h"
#include "CycleFinder.h"

BellmanFordSP::BellmanFordSP(WeightedDigraph &g, int s)
    : distTo(g.V()), edgeTo(g.V()), onQueue(g.V()), callsToRelax(0)
{
    for (int i = 0; i < g.V(); ++i)
    {
        distTo[i] = DBL_MAX;
        onQueue[i] = false;
    }

    distTo[s] = 0.0;
    que.push(s);
    onQueue[s] = true;
    while (!que.empty() && !hasNegativeCycle())
    {
        int v = que.front();
        que.pop();
        onQueue[v] = false;

        relax(g, v);
    }
}

void BellmanFordSP::relax(WeightedDigraph &g, int v)
{
    for (auto e : g.adj(v))
    {
        int w = e.to();

        if (distTo[w] > distTo[v] + e.getWeight())
        {
            distTo[w] = distTo[v] + e.getWeight();
            edgeTo[w] = e;

            if (!onQueue[w])
            {
                que.push(w);
                onQueue[w] = true;
            }
        }

        if (++callsToRelax % g.V() == 0)
            findNegativeCycle();
    }
}


std::stack<DirectedEdge> BellmanFordSP::pathTo(int v)
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

void BellmanFordSP::findNegativeCycle()
{
    WeightedDigraph shortestPathsTree(edgeTo.size());
    for (int v = 0; v < edgeTo.size(); ++v)
    {
        if (distTo[v] != DBL_MAX && distTo[v] != 0)     // 等价于没有边到该点的话就添加
            shortestPathsTree.addEdge(edgeTo[v]);
    }

     CycleFinder cf(shortestPathsTree);
    cycle = cf.getCycle();
}
