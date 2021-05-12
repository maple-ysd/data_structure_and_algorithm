#ifndef CONNECTEDCOMPONENTSRECURSIVEDFS_H_
#define CONNECTEDCOMPONENTSRECURSIVEDFS_H_

/** 递归DFS，计算连通分量
 */

#include "Graph.h"
class ConnectedComponentsRecursiveDFS
{
public:
    ConnectedComponentsRecursiveDFS(Graph &g)
    {
        visited = new bool[g.vertices()];
        id = new int[g.vertices()];
        cnt = 0;

        for (int v = 0; v < g.vertices(); ++v)
        {
            visited[v] = false;
            id[v] = v;
        }

        for (int v = 0; v < g.vertices(); ++v)
        {
            if (!visited[v])
            {
                dfs(g, v);
                ++cnt;
            }
        }
    }
    void dfs(Graph &g, int v)
    {
        visited[v] = true;
        id[v] = cnt;

        for (auto x : g.getAdjacentList(v))
        {
            if (!visited[x])
            {
                dfs(g, x);
            }
        }
    }
    ~ConnectedComponentsRecursiveDFS()
    {
        delete[] visited;
        delete[] id;
    }
    bool connected(int vex1, int vex2)
    {
        return id[vex1] == id[vex2];
    }
    int getID(int vex) { return id[vex]; }
    int count() { return cnt; }
private:
    bool *visited;
    int *id;
    int cnt;
};

#endif // CONNECTEDCOMPONENTSRECURSIVEDFS_H_
