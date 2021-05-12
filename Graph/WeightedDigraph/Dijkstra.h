#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

/** Dijkstra�㷨 O��ElogV��
 *  ����Դ������Ķ��������ɳڣ���ÿһ��ѡ��δ�������·���еľ���Դ������ĵ㣩��
 *
 *  Ҫ��û�и�Ȩ�ߣ�����
 *
 *  ��һ��distTo�����ʾԴ�㵽��������ľ��룬��ʼʱdistTo[s] = 0;����dist[]��Ϊ����󣬽�s�����������ȶ���
 *  �������ȶ��в��յ�����£�
 *  ���Ӷ���Ԫ��s���ɳ�s�������ڽӱߣ�������distTo[w] > distTo[s] + e.getWeight() ����distTo[w]
 *  ��wδ�������ȶ��У�����룻���Ѽ��룬���޸��������ȶ������Ӧ��ֵ
 *  �ظ�������̣����Ӷ���Ԫ�ء�����
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
