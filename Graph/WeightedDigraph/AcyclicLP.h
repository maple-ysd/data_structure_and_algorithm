#ifndef ACYCLICLP_H_
#define ACYCLICLP_H_

/** 单点最长路径，只要简单修改下distTo的初始值DBL_MAX->DBL_MIN
 *  此外，将relax成功的条件由> -> < 即可；
 *  另一种实现方法：
 *  private对象改成一个指向AcyclicSP对象的指针；
 *  在构造函数里创建该对象（前提：将WeightedGraph里变得权重全部取反）
 *  用AcyclicSP的方法实现AcyclicLP
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
