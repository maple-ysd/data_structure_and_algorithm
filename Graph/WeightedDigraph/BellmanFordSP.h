#ifndef BELLMANFORDSP_H_
#define BELLMANFORDSP_H_

/** BellmanFord���·���㷨����Ҫ���������л��͸�Ȩ�ߵ������ͬʱҲ��ʶ��ͼ�еĸ�Ȩ��
 * O��EV��
 */

#include "WeightedDigraph.h"
#include <vector>
#include <stack>
#include <queue>
#include <cfloat>

class BellmanFordSP
{
public:
    BellmanFordSP(WeightedDigraph &g, int s);
    double getDistTo(int v) { return distTo[v]; }
    bool hasPathTo(int v) { return distTo[v] != DBL_MAX; }
    std::stack<DirectedEdge> pathTo(int v);
    void findNegativeCycle();
    bool hasNegativeCycle() { return !cycle.empty(); }
    std::stack<DirectedEdge> negativeCycle() { return cycle; }
private:
    void relax(WeightedDigraph &g, int v);
    std::vector<double> distTo;
    std::vector<DirectedEdge> edgeTo;
    std::vector<bool> onQueue;
    std::queue<int> que;
    int callsToRelax;
    std::stack<DirectedEdge> cycle;
};

#endif // BELLMANFORDSP_H_
