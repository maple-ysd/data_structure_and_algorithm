#include "PrimMST.h"
#include <cfloat>

PrimMST::PrimMST(WeightedGraph &wg): pq(wg.V())
{
    edgeTo = new Edge*[wg.V()];
    distTo = new double[wg.V()];
    visited = new bool[wg.V()];

    for (int i = 0; i < wg.V(); ++i)
    {
        visited[i] = false;
        distTo[i] = DBL_MAX;
        edgeTo[i] = nullptr;
    }

    distTo[0] = 0.0;
    pq.insert(0, 0.0);
    while (!pq.empty())
        visit(wg, pq.deleteMin());

    //
    for (int i = 1; i < wg.V(); ++i)
    {
        q.push(edgeTo[i]);
        weight += distTo[i];
    }
}

PrimMST::~PrimMST()
{
    delete[] visited;
    delete[] edgeTo;
    delete[] distTo;
}

void PrimMST::visit(WeightedGraph &wg, int v)
{
    // 将顶点加入树中
    visited[v] = true;

    for (Edge *e : wg.adj(v))
    {
        int w = e->other(v);

        if (visited[w]) continue;
        if (e->getWeight() < distTo[w])
        {
            edgeTo[w] = e;
            distTo[w] = e->getWeight();
            if (pq.contains(w)) pq.change(w, distTo[w]);
            else pq.insert(w, distTo[w]);
        }
    }
}
