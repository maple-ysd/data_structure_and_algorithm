#include "WeightedCycle.h"

WeightedCycle::WeightedCycle(WeightedGraph &wg)
{
    visited = new bool[wg.V()];
    edgeTo = new Edge*[wg.V()];
    onStack = new bool[wg.V()];
    cycleFound = false;

    for (int i = 0; i < wg.V(); ++i)
    {
        visited[i] = false;
        onStack[i] = false;
        edgeTo[i] = nullptr;
    }

    for (int v = 0; v < wg.V(); ++v)
    {
        if (cycleFound) break;
        if (!visited[v])
            dfs(wg, v, v);
    }
}

void WeightedCycle::dfs(WeightedGraph &wg, int origin, int v)
{
     onStack[v] = true;
     visited[v] = true;

     for (Edge* neighbor : wg.adj(v))
     {
         int neighborVertex = neighbor->other(v);
         if (neighborVertex == origin) continue;

         if (hasCycle()) return;
         else if (!visited[neighborVertex])
         {
             edgeTo[neighborVertex] = neighbor;
             dfs(wg, v, neighborVertex);
         }
         else if (onStack[neighborVertex])
         {
             cycleFound = true;

             for (int currVertex = v; currVertex != neighborVertex; currVertex = edgeTo[currVertex]->other(currVertex))
                cycle.push(edgeTo[currVertex]);
             cycle.push(neighbor);
         }
     }
     onStack[v] = false;
}
