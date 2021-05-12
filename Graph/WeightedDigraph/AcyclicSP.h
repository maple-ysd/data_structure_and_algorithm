#ifndef ACYCLICSP_H_
#define ACYCLICSP_H_

/** �޻���Ȩ����ͼ�����·���㷨
 *  O��E������
 *  ����������������������ȶ��У�O(1)
 *  �������������ʵ���õ��ǻ��ڶ��еģ����ڶ�������ͼ�������
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
