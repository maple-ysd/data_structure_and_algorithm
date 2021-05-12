#ifndef BREADFIRSTPATH_H_
#define BREADFIRSTPATH_H_

/** 广度优先路径，（可用于单源最短路径问题）
 * O（V + E）
 */

#include "Graph.h"
#include <queue>
#include <stack>
class BreadFirstPath
{
public:
    BreadFirstPath(Graph &g, int s)
    {
        // 初始化
        parent = new int[g.vertices()];
        source = s;
        distTo = new int[g.vertices()];

        for (int i = 0; i < g.vertices(); ++i)
        {
            parent[i] = -1;
            distTo[i] = -1;
        }
        distTo[s] = 0;
        // bfs
        std::queue<int> q;
        q.push(source);
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (auto x : g.getAdjacentList(curr))
            {
                if (distTo[x] == -1)
                {
                    q.push(x);

                    parent[x] = curr;
                    distTo[x] = distTo[curr] + 1;
                }
            }
        }
    }
    int getDistTo(int vex)
    {
        return distTo[vex];
    }
    bool hasPathTo(int vex)
    {
        return distTo[vex] != -1;
    }
    std::stack<int> getPathTo(int vex)
    {
        std::stack<int> sp;
        for (int v = vex; parent[v] != -1; v = parent[v])
        {
            sp.push(v);
        }
        sp.push(source);
        return sp;
    }
    void printPathTo(int vex)
    {
        std::stack<int> s = getPathTo(vex);
        int v;
        bool first = true;
        while (!s.empty())
        {
            if (first)
                first = false;
            else
                std::cout << "->";
            v = s.top();
            s.pop();
            std::cout << v;
        }
        std::cout << std::endl;
    }
    ~BreadFirstPath()
    {
        delete[] parent;
        delete[] distTo;
    }
private:
    int *parent;
    int source;
    int *distTo;
};



#endif // BREADFIRSTPATH_H_
