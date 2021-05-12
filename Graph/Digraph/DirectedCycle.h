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
    std::stack<int> cycle;      // �����е����ж���
    bool *onStack;              // �ݹ���õ�ջ�ϵ����ж���
};

#endif // DIRECTEDCYCLE_H_
