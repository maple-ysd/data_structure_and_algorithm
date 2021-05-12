#ifndef BREADTHFIRSTDIRECTEDPATH_H_
#define BREADTHFIRSTDIRECTEDPATH_H_

#include "Digraph.h"
#include <stack>

class BreadthFirstDirectedPath
{
public:
    BreadthFirstDirectedPath(Digraph &g, int s);
    ~BreadthFirstDirectedPath() { delete[] visited; delete[] parent; }
    bool hasPathTo(int vex) { return visited[vex]; }
    std::stack<int> pathTo(int vex);
private:
    bool *visited;
    int *parent;
    int source;
};

#endif // BREADTHFIRSTDIRECTEDPATH_H_
