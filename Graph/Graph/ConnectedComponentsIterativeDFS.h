#ifndef CONNECTEDCOMPONENTSITERATIVEDFS_H_
#define CONNECTEDCOMPONENTSITERATIVEDFS_H_

/** DFS迭代，算连通分量
 */
#include "SingleList.h"
#include "Graph.h"
#include <stack>

class ConnectedComponentsIterativeDFS
{
public:
    ConnectedComponentsIterativeDFS(Graph &g)
    {
        visited = new bool[g.vertices()];
        id = new int[g.vertices()];
        cnt = 0;
        // 初始化
        for (int i = 0; i < g.vertices(); ++i)
        {
            visited[i] = false;
            id[i] = i;
        }
        // 对每一个未被访问过的顶点调用dfs
        for (int i = 0; i < g.vertices(); ++i)
        {
            if (!visited[i])
            {
                iterativeDFS(g, i);
                ++cnt;
            }
        }
    }
    void iterativeDFS(Graph &g, int i)
    {
        std::stack<int> s;
        s.push(i);
        visited[i] = true;
        // 初始化一个迭代器数组，对应单链表数组
        SingleList<int>::iter adjacentIterator[g.vertices()];
        for (int i = 0; i < g.vertices(); ++i)
            adjacentIterator[i] = g.getAdjacentList(i).begin();

        while (!s.empty())
        {
            int v = s.top();

            if (adjacentIterator[v].hasNext())
            {
                int neighbor = *adjacentIterator[v];
                if (!visited[neighbor])
                {
                    s.push(neighbor);
                    visited[neighbor] = true;
                    id[neighbor] = cnt;
                }
                ++adjacentIterator[v];
            }
            else
            {
                s.pop();
            }
        }
    }
    ~ConnectedComponentsIterativeDFS()
    {
        delete visited;
        delete id;
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


#endif // CONNECTEDCOMPONENTSITERATIVEDFS_H_
