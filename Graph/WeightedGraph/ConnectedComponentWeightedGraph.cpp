#include "ConnectedComponentWeightedGraph.h"

ConnectedComponentWeightedGraph::ConnectedComponentWeightedGraph(WeightedGraph &wg)
{
    visited = new bool(wg.V());
    id = new int[wg.V()];
    cnt = 0;
    for (int i = 0; i < wg.V(); ++i)
    {
        visited[i] = false;
        id[i] = i;
    }

    for (int v = 0; v < wg.V(); ++v)
    {
        if (!visited[v])
        {
            dfs(wg, v, v);
            ++cnt;
        }
    }
}

void ConnectedComponentWeightedGraph::dfs(WeightedGraph &wg, int origin, int v)
{
    visited[v] = true;
    id[v] = cnt;

    for (auto neighbor : wg.adj(v))
    {
        int neighborVertex = neighbor->other(v);
        if (v == neighborVertex) continue;

        if (!visited[neighborVertex])
            dfs(wg, v, neighborVertex);
    }
}
