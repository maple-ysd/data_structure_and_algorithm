#ifndef CYCLE_H_
#define CYCLE_H_

/** �õݹ�DFS�ж��Ƿ��л�
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
//            else if (neighbor != origin                 // �����黷
//                    && neighbor != v                    // �����Ի�
//                    && parent(neighbor) != v)           // ����ƽ�б�
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
