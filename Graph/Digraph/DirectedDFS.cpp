#include "DirectedDFS.h"

DirectedDFS::DirectedDFS(Digraph &g, int s)
{
    visited = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
        visited[i] = false;
    dfs(g, s);
}

DirectedDFS::DirectedDFS(Digraph &g, std::initializer_list<int> il)
{
    visited = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
        visited[i] = false;
    for (auto s : il)
    {
        if (!visited[s]) dfs(g, s);
    }
}

DirectedDFS::DirectedDFS(Digraph &g, std::unordered_set<int> il)
{
    visited = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
        visited[i] = false;
    for (auto s : il)
    {
        if (!visited[s]) dfs(g, s);
    }
}

void DirectedDFS::dfs(Digraph &g, int s)
{
    visited[s] = true;
    for (auto neighbor : g.adjacent(s))
    {
        if (!visited[neighbor])
            dfs(g, neighbor);
    }
}
