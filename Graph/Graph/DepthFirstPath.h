#ifndef DEPTHFIRSTPATH_H_
#define DEPTHFIRSTPATH_H_

/** 深度优先路径
 *  O（V + E）
 */

#include <iostream>
#include <stack>
#include "Graph.h"

class DepthFirstPath
{
public:
    DepthFirstPath(Graph &g, int s)
    {
        visited = new bool[g.vertices()];
        parent = new int[g.vertices()];
        for (int i = 0; i < g.vertices(); ++i)
        {
            parent[i] = -1;
            visited[i] = false;
        }
        source = s;
        dfs(g, s);
    }
    void dfs(Graph &g, int s)
    {
        visited[s] = true;
        for (auto x : g.getAdjacentList(s))
        {
            if (!visited[x])
            {
                parent[x] = s;
                dfs(g, x);
            }
        }
    }
    ~DepthFirstPath()
    {
        delete[] visited;
        delete[] parent;
    }
    bool hasPathTo(int vex) { return visited[vex]; }
    std::stack<int> getPathTo(int vex)
    {
        std::stack<int> s;
        for (int v = vex; parent[v] != -1; v = parent[v])
        {
            s.push(v);
        }
        s.push(source);
        return s;
    }
    void printPathTo(int vex)
    {
        std::stack<int> s = getPathTo(vex);
        bool first = true;
        while (!s.empty())
        {
            if (first)
                first = false;
            else
                std::cout << "->";
            std::cout << s.top();
            s.pop();
        }
        std::cout << std::endl;
    }
private:
    bool *visited;
    int *parent;
    int source;
};

#include "Graph.h"



#endif // DEPTHFIRSTPATH_H_
