#include "Topological.h"

Topological::Topological(WeightedDigraph &g): indegrees(g.V())
{
    for (int i = 0; i < g.V(); ++i)
        indegrees[i] = 0;
    for (auto e : g.edges())
        ++indegrees[e.to()];

    std::queue<int> q;
    for (int v = 0; v < g.V(); ++v)
    {
        if (indegrees[v] == 0)
            q.push(v);
    }

    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        topoOrder.push_back(v);

        for (auto e: g.adj(v))
        {
            int w = e.to();
            --indegrees[w];
            if (indegrees[w] == 0)
                q.push(w);

        }
    }
}
