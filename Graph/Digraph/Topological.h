#ifndef TOPOLOGICAL_H_
#define TOPOLOGICAL_H_

#include "Digraph.h"
#include <stack>

class Topological
{
public:
    Topological(Digraph &g);
    std::stack<int> getOrder() { return order; }
    bool isDAG() { return !order.empty(); }     // 判断是否为有向无环图
private:
    std::stack<int> order;
};

#endif // TOPOLOGICAL_H_
