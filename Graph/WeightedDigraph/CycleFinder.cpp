#include "CycleFinder.h"

CycleFinder::CycleFinder(WeightedDigraph &g): visited(g.V()),edgeTo(g.V()), onStack(g.V()), cycleFound(false)
{
    for (int v = 0; v < g.V(); ++v)
    {
        visited[v] = false;
        onStack[v] = false;
    }

    for (int v = 0; v < g.V(); ++v)
    {
        if (cycleFound) break;
        if (!visited[v])
            dfs(g, v);
    }
}

void CycleFinder::dfs(WeightedDigraph &g, int v)
{
    onStack[v] = true;
    visited[v] = true;

    for (auto e : g.adj(v))
    {
        int w = e.to();

        if (hasCycle()) return;
        else if (!visited[w])
        {
            edgeTo[w] = e;
            dfs(g, w);
        }
        else if (onStack[w])
        {
            cycleFound = true;
            for (int currVertex = v; v != w; v = edgeTo[v].from())
                cycle.push(edgeTo[v]);
            cycle.push(e);
        }
    }
    onStack[v] = false;
}
