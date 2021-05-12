#include "LazyPrimMST.h"

LazyPrimMST::LazyPrimMST(WeightedGraph &wg)
{
    visited = new bool[wg.V()];
    weight = 0.0;

    for (int i = 0; i < wg.V(); ++i)
        visited[i] = false;

    visit(wg, 0);
    while (!pq.empty())
    {
        Edge *e = pq.top();
        pq.pop();
        int vex1 = e->either();
        int vex2 = e->other(vex1);

        // 如果该边的两个顶点都已经加入生成树， 则忽略它
        if (visited[vex1] && visited[vex2]) continue;

        mst.push(e);
        weight += e->getWeight();
        if (!visited[vex1]) visit(wg, vex1);
        if (!visited[vex2]) visit(wg, vex2);
    }
}

void LazyPrimMST::visit(WeightedGraph &wg, int v)
{
    visited[v] = true;

    for (Edge* e : wg.adj(v))
    {
        if (!visited[e->other(v)])
        {
            pq.push(e);
        }
    }
}
