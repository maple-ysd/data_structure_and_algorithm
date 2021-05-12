#ifndef PRIMMST_H_
#define PRIMMST_H_

/** 该方法与LazyPrimMST的区别在于，及时处理无效的边，
 * 使优先队列里保存的永远是到当前为止从已加入最小生成树里面的顶点到生成树之外的每一个顶点的最小边
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
    Edge **edgeTo;   // 离树的最短边
    double *distTo; // 离树的最短边的距离
    bool *visited;
    IndexMinPriorityQueue<double> pq; // 合格的交叉边

    double weight = 0;
    std::queue<Edge*> q;
};

#endif // PRIMMST_H_
