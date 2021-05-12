#include "KruskalMST.h"
#include "UF.h"
#include <queue>

KruskalMST::KruskalMST(WeightedGraph &wg)
{
    std::priority_queue<Edge*, std::vector<Edge*>, Greater> pq;
    // 这里如果最小优先队列是自己定义的，可以接受一个数组作为参数，
    // 采用sink方法来构造，只需要线性时间即可完成， 这里为O（ElogE）
    for (auto e : wg.allEdges())
    {
        pq.push(e);
    }
    UF uf(wg.V());
    while (!pq.empty() && mst.size() < wg.V() - 1)
    {
        Edge *e = pq.top();
        pq.pop();
        int v = e->either(), w = e->other(v);
        if (uf.connected(v, w))  continue;

        uf.Union(v, w);
        mst.push(e);
    }
}
