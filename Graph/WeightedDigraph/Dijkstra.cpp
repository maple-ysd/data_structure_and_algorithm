#include "Dijkstra.h"

using namespace std;

Dijkstra::Dijkstra(WeightedDigraph &g, int s): edgeTo(g.V()), distTo(g.V()), pq(g.V())
{
    for (int v = 0; v < g.V(); ++v)
        distTo[v] = DBL_MAX;
    distTo[s] = 0;
    pq.insert(s, 0.0);
    while (!pq.empty())
        relax(g, pq.deleteMin());
}

void Dijkstra::relax(WeightedDigraph &g, int v)
{
    for (auto e : g.adj(v))
    {
        int w = e.to();
        if (distTo[w] > distTo[v] + e.getWeight())
        {
            distTo[w] = distTo[v] + e.getWeight();
            edgeTo[w] = e;

            if (pq.contains(w)) pq.change(w, distTo[w]);
            else pq.insert(w, distTo[w]);
        }
    }
}


stack<DirectedEdge> Dijkstra::pathTo(int v)
{
    stack<DirectedEdge> s;
    while (distTo[v] != 0.0)
    {
        s.push(edgeTo[v]);
        v = edgeTo[v].from();
    }
    return s;
}
