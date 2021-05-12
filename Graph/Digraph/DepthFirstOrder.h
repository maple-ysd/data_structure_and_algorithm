#ifndef DEPTHFIRSTORDER_H_
#define DEPTHFIRSTORDER_H_

#include "Digraph.h"
#include <queue>
#include <stack>

class DepthFirstOrder
{
public:
    DepthFirstOrder(Digraph &g);
    ~DepthFirstOrder() { delete visited; }
    std::queue<int> preOrder() { return pre; }
    std::queue<int> postOrder() { return post; }
    std::stack<int> reversePostOrder() { return reversePost; }
private:
    void dfs(Digraph &g, int v);
    bool *visited;
    std::queue<int> pre;
    std::queue<int> post;
    std::stack<int> reversePost;
};

#endif // DEPTHFIRSTORDER_H_
