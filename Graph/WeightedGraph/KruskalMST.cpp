#include "KruskalMST.h"
#include "UF.h"
#include <queue>

KruskalMST::KruskalMST(WeightedGraph &wg)
{
    std::priority_queue<Edge*, std::vector<Edge*>, Greater> pq;
    // ���������С���ȶ������Լ�����ģ����Խ���һ��������Ϊ������
    // ����sink���������죬ֻ��Ҫ����ʱ�伴����ɣ� ����ΪO��ElogE��
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
