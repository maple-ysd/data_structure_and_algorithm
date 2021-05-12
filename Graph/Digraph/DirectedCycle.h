#ifndef DIRECTEDCYCLE_H_
#define DIRECTEDCYCLE_H_

#include "Digraph.h"
#include <stack>

class DirectedCycle
{
public:
    DirectedCycle(Digraph &g);
    ~DirectedCycle() { delete visited; delete parent; delete onStack; }
    bool hasCycle() { return !cycle.empty(); }
    std::stack<int> getCycle() { return cycle; }
private:
    void dfs(Digraph &g, int v);
    bool *visited;
    int *parent;
    std::stack<int> cycle;      // 有向环中的所有顶点
    bool *onStack;              // 递归调用的栈上的所有顶点
};

#endif // DIRECTEDCYCLE_H_
