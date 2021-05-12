#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

/** Dijkstra算法 O（ElogV）
 *  将距源点最近的顶点依次松弛，（每一次选择未加入最短路径中的距离源点最近的点）。
 *
 *  要求：没有负权边！！！
 *
 *  用一个distTo数组表示源点到其他个点的距离，开始时distTo[s] = 0;其他dist[]设为无穷大，将s加入索引优先队列
 *  索引优先队列不空的情况下：
 *  出队队首元素s，松弛s的所有邻接边，若满足distTo[w] > distTo[s] + e.getWeight() 更新distTo[w]
 *  若w未加入优先队列，则加入；若已加入，则修改其在优先队列里对应的值
 *  重复上面过程，出队队首元素。。。
 */

#include "WeightedDigraph.h"
#include "IndexMinPriorityQueue.h"
#include <cfloat>
#include <vector>
#include <stack>

class Dijkstra
{
public:
    Dijkstra(WeightedDigraph &g, int s);
    double getDistTo(int v ) { return distTo[v]; }
    bool hasPathTo(int v) { return distTo[v] != DBL_MAX; }
    std::stack<DirectedEdge> pathTo(int v);
private:
    void relax(WeightedDigraph &g, int v);
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> distTo;
    IndexMinPriorityQueue pq;
};


#endif // DIJKSTRA_H_
