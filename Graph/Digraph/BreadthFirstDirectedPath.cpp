#include "BreadthFirstDirectedPath.h"
#include <queue>

BreadthFirstDirectedPath::BreadthFirstDirectedPath(Digraph &g, int s)
{
    visited = new bool[g.vertices()];
    for (int i = 0; i < g.vertices(); ++i)
        visited[i] = false;

    parent = new int[g.vertices()];
    source = s;

    visited[source] = true;
    std::queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int vex = q.front();
        q.pop();

        for (auto neighbor: g.adjacent(vex))
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = vex;
                q.push(neighbor);
            }
        }
    }
}

std::stack<int> BreadthFirstDirectedPath::pathTo(int vex)
{
    std::stack<int> s;
    for (int v = vex; v != source; v = parent[v])
        s.push(v);
    s.push(source);
    return s;
}
