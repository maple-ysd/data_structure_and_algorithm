#ifndef DIRECTEDDFS_H_
#define DIRECTEDDFS_H_
/** 单点可达性与多点可达性
 *
 */

 #include <initializer_list>
 #include <unordered_set>
#include "Digraph.h"

class DirectedDFS
{
public:
    DirectedDFS(Digraph &g, int s);
    DirectedDFS(Digraph &g, std::initializer_list<int> il);
    DirectedDFS(Digraph &g, std::unordered_set<int> il);
    ~DirectedDFS() { delete[] visited; }
    bool hasPathTo(int vex) { return visited[vex]; }
private:
    bool *visited;
    void dfs(Digraph &g, int s);
};

#endif // DIRECTEDDFS_H_
