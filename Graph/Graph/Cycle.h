#ifndef CYCLE_H_
#define CYCLE_H_

/** 用递归DFS判断是否有环
 *
 */

#include "Graph.h"

class Cycle
{
public:
    Cycle(Graph &g)
    {
        visited = new bool[g.vertices()];
        hasCycle = false;
        for (int v = 0; v < g.vertices(); ++v)
            visited[v] = false;
        for (int v = 0; v < g.vertices(); ++v)
        {
            if (!visited[v])
                dfs(g, v, v);
        }
    }
    void dfs(Graph &g, int v, int origin)
    {
        visited[v] = true;

        for (auto neighbor : g.getAdjacentList(v))
        {
            if (!visited[neighbor])
                dfs(g, neighbor, v);
            else if (neighbor != origin)
//            else if (neighbor != origin                 // 正常查环
//                    && neighbor != v                    // 避免自环
//                    && parent(neighbor) != v)           // 避免平行边
                hasCycle = true;
        }
    }
    ~Cycle() { delete[] visited; }
    bool HasCycle() { return hasCycle; }
private:
    bool *visited;
    bool hasCycle;
};
#endif // CYCLE_H_
