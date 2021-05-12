#ifndef CONNECTEDCOMPONENTSITERATIVEDFS_H_
#define CONNECTEDCOMPONENTSITERATIVEDFS_H_

/** DFS����������ͨ����
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
        // ��ʼ��
        for (int i = 0; i < g.vertices(); ++i)
        {
            visited[i] = false;
            id[i] = i;
        }
        // ��ÿһ��δ�����ʹ��Ķ������dfs
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
        // ��ʼ��һ�����������飬��Ӧ����������
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
