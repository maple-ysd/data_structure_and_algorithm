#include "DepthFirstDirectedPath.h"

DepthFirstDirectedPath::DepthFirstDirectedPath(Digraph &g, int s)
{
    visited = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
        visited[i] = false;
    parent = new int[g.vertices()];
    source = s;
    dfs(g, s);
}

void DepthFirstDirectedPath::dfs(Digraph &g, int vex)
{
    visited[vex] = true;

    for (auto x : g.adjacent(vex))
    {
        if (!visited[x])
        {
            parent[x] = vex;
            dfs(g, x);
        }
    }
}

std::stack<int> DepthFirstDirectedPath::pathTo(int vex)
{
    std::stack<int> s;
    for (int v = vex; v != source; v = parent[v])
    {
        s.push(v);
    }
    s.push(source);
    return s;
}
