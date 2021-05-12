#include "DirectedCycle.h"

DirectedCycle::DirectedCycle(Digraph &g)
{
    visited = new bool[g.vertices()];
    parent = new int[g.vertices()];
    onStack = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
    {
        visited[i] = false;
        onStack[i] = false;
    }
    for (int v = 0; v < g.vertices(); ++v)
        if (!visited[v])
            dfs(g, v);
}

void DirectedCycle::dfs(Digraph &g, int v)
{
    visited[v] = true;
    onStack[v] = true;
    for (auto w : g.adjacent(v))
    {
        if (hasCycle()) return;
        else if (!visited[w])
        {
            parent[w] = v;
            dfs(g, w);
        }
        else if (onStack[w])
        {
            for (int x = v; x != w; x = parent[x])
            {
                cycle.push(x);
            }
            cycle.push(w);
            cycle.push(v);
        }
    }
    onStack[v] = false;
}
