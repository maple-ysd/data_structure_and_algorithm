#ifndef LAZYPRIMMST_H_
#define LAZYPRIMMST_H_

/** Prim �㷨������С������
 * ����˼�뽫ͼһ��Ϊ����һ��Ϊ�Ѽ�����С�������Ķ��㼯�ϣ� һ��Ϊ������Ķ��㼯�ϣ�
 * Ȼ��ѡһ�������������ϵı������С�߼��룬��������Լ����ڵıߣ����õ��µ���������
 * �ظ�������̡�
 */

#include "WeightedGraph.h"
#include <queue>
#include <vector>

class LazyPrimMST
{
public:
    LazyPrimMST(WeightedGraph &wg);
    ~LazyPrimMST() { delete[] visited; }
    std::queue<Edge*> edges() { return mst; }
    double getWeight() { return weight; }
private:
    void visit(WeightedGraph &wg, int v);
    bool *visited;
    std::queue<Edge*> mst;
    double weight;

    std::priority_queue<Edge*, std::vector<Edge*>, Greater> pq;
};


#endif // LAZYPRIMMST_H_
