#ifndef DEPTHFIRSTSEARCH_H_
#define DEPTHFIRSTSEARCH_H_

/** 深度优先搜索
 *  O（V + E）
 */
#include "Graph.h"

class DepthFirstSearch
{
public:
    DepthFirstSearch(Graph &g, int s)
    {
        visited = new bool[g.vertices()];
        cnt = 0;
        for (int i = 0; i < g.vertices(); ++i)
            visited[i] = false;
        dfs(g, s);
    }
    void dfs(Graph &g, int s)
    {
        visited[s] = true;
        ++cnt;

        for (auto neighbor : g.getAdjacentList(s))
            if (!visited[neighbor])
                dfs(g, neighbor);
    }
    ~DepthFirstSearch() { delete[] visited; }
    bool marked(int vex) { return visited[vex]; }
    int count() { return cnt; }
private:
    bool *visited;
    int cnt;

};


#endif // DEPTHFIRSTSEARCH_H_
