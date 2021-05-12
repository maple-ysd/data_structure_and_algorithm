#ifndef TWOCOLORS_H_
#define TWOCOLORS_H_

/** DFSµÝ¹é£º ¶þ·ÖÍ¼
 */
#include "Graph.h"

class TwoColors
{
public:
    TwoColors(Graph &g)
    {
        visited = new bool[g.vertices()];
        color = new bool[g.vertices()];
        isTwoColors = true;

        for (int v = 0; v < g.vertices(); ++v)
        {
            visited[v] = false;
        }
        color[0] = true;
        for (int v = 0; v < g.vertices(); ++v)
        {
            if (!visited[v])
                dfs(g, v);
        }
    }
    void dfs(Graph &g, int v)
    {
        visited[v] = true;

        for (auto x : g.getAdjacentList(v))
        {
            if (!visited[x])
            {
                color[x] = !color[v];
                dfs(g, x);
            }
            else if (color[x] == color[v])
                isTwoColors = false;
        }
    }
    ~TwoColors()
    {
        delete[] visited;
        delete[] color;
    }
    bool isBipartite() { return isTwoColors; }
private:
    bool *visited;
    bool *color;
    bool isTwoColors;
};

#endif // TWOCOLORS_H_
