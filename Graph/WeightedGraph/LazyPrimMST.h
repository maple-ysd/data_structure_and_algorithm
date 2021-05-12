#ifndef LAZYPRIMMST_H_
#define LAZYPRIMMST_H_

/** Prim 算法生成最小生成树
 * 核心思想将图一分为二，一份为已加入最小生成树的顶点集合， 一份为待加入的顶点集合，
 * 然后选一个连接两个集合的边里的最小边加入，（不算各自集合内的边），得到新的两个集合
 * 重复上面过程。
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
