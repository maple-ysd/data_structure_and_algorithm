#include "KosarajuSCC.h"
#include "DepthFirstOrder.h"
#include <stack>

KosarajuSCC::KosarajuSCC(Digraph &g)
{
    visited = new bool[g.vertices()];
    id = new int[g.vertices()];
    cnt = 0;
    for (int v = 0; v < g.vertices(); ++v)
    {
        visited[v] = false;
        id[v] = v;
    }
    Digraph *rg = g.reverse();      // 记得要delete该指针
    DepthFirstOrder dfo(*rg);
    std::stack<int> s = dfo.reversePostOrder();
    delete rg;
    while (!s.empty())
    {
        int v = s.top();
        s.pop();
        if (!visited[v])
        {
            dfs(g, v);
            ++cnt;
        }
    }
}

void KosarajuSCC::dfs(Digraph &g, int v)
{
    visited[v] = true;
    id[v] = cnt;
    for (auto w : g.adjacent(v))
        if (!visited[w])
            dfs(g, w);
}
