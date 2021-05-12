#ifndef ACYCLICSP_H_
#define ACYCLICSP_H_

/** 无环加权有向图的最短路径算法
 *  O（E）线性
 *  基于拓扑排序（替代索引优先队列）O(1)
 *  这里拓扑排序的实现用的是基于队列的（基于而非逆向图的逆后序）
 */

#include "WeightedDigraph.h"
#include <vector>
#include <stack>
#include<cfloat>

class AcyclicSP
{
public:
    AcyclicSP(WeightedDigraph &g, int s);
    double getDistTo(int v) { return distTo[v]; }
    bool hasPathTo(int v) { return distTo[v] != DBL_MAX; }
    std::stack<DirectedEdge> pathTo(int v);
private:
    void relax(WeightedDigraph &g, int v);
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> distTo;
};

#endif // ACYCLICSP_H_
