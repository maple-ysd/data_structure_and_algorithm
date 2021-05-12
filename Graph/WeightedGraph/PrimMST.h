#ifndef PRIMMST_H_
#define PRIMMST_H_

/** �÷�����LazyPrimMST���������ڣ���ʱ������Ч�ıߣ�
 * ʹ���ȶ����ﱣ�����Զ�ǵ���ǰΪֹ���Ѽ�����С����������Ķ��㵽������֮���ÿһ���������С��
 */
#include "WeightedGraph.h"
#include "IndexMinPriorityQueue.h"
#include <queue>

class PrimMST
{
public:
    PrimMST(WeightedGraph &wg);
    ~PrimMST();
    std::queue<Edge*> edges() { return q; }
    double getWeight() { return weight; }
private:
    void visit(WeightedGraph &wg, int v);
    Edge **edgeTo;   // ��������̱�
    double *distTo; // ��������̱ߵľ���
    bool *visited;
    IndexMinPriorityQueue<double> pq; // �ϸ�Ľ����

    double weight = 0;
    std::queue<Edge*> q;
};

#endif // PRIMMST_H_
