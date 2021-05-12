#include "DepthFirstOrder.h"

DepthFirstOrder::DepthFirstOrder(Digraph &g)
{
    visited = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
        visited[i] = false;
    for (int v = 0; v < g.vertices(); ++v)
        if (!visited[v]) dfs(g, v);
}

void DepthFirstOrder::dfs(Digraph &g, int v)
{
    visited[v] = true;
    pre.push(v);

    for (auto w : g.adjacent(v))
        if (!visited[w]) dfs(g, w);

    post.push(v);
    reversePost.push(v);
}
