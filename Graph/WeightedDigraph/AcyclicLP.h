#ifndef ACYCLICLP_H_
#define ACYCLICLP_H_

/** �����·����ֻҪ���޸���distTo�ĳ�ʼֵDBL_MAX->DBL_MIN
 *  ���⣬��relax�ɹ���������> -> < ���ɣ�
 *  ��һ��ʵ�ַ�����
 *  private����ĳ�һ��ָ��AcyclicSP�����ָ�룻
 *  �ڹ��캯���ﴴ���ö���ǰ�᣺��WeightedGraph����Ȩ��ȫ��ȡ����
 *  ��AcyclicSP�ķ���ʵ��AcyclicLP
 */


#include "WeightedDigraph.h"
#include <stack>
#include <vector>

const int Min_Weight = -1.0e9;

class AcyclicLP
{
public:
    AcyclicLP(WeightedDigraph &g, int s);
    bool hasPathTo(int v) { return distTo[v] != Min_Weight; }
    double getDistTo(int v) { return distTo[v]; }
    std::stack<DirectedEdge> pathTo(int v);
private:
    void relax(WeightedDigraph & wg, int v);
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> distTo;
};

#endif // ACYCLICLP_H_
