#ifndef DEPTHFIRSTDIRECTEDPATH_H_
#define DEPTHFIRSTDIRECTEDPATH_H_

#include "Digraph.h"
#include <stack>

class DepthFirstDirectedPath
{
public:
    DepthFirstDirectedPath(Digraph &g, int s);
    ~DepthFirstDirectedPath() { delete[] visited; delete[] parent; }
    bool hasPathTo(int vex) { return visited[vex]; }
    std::stack<int> pathTo(int vex);
private:
    void dfs(Digraph &g, int vex);
    bool *visited;
    int *parent;
    int source;
};

#endif // DEPTHFIRSTDIRECTEDPATH_H_
