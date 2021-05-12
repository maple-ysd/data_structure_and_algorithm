#include "KShortestPath.h"
#include <queue>
#include <functional>

Path::Path(int v)
{
    verticesInPath.insert(v);
    weight = 0;
    lastVertice = v;
}
Path::Path(Path rhs, DirectedEdge e): path(rhs.path), verticesInPath(rhs.verticesInPath), weight(rhs.weight)
{
    path.push_back(e);
    verticesInPath.insert(e.to());
    weight += e.getWeight();
    lastVertice = e.to();
}

//
std::vector<Path> KShortestPaths(WeightedDigraph &g, int s, int t, int k)
{
    int cnt = 0;        // 记录s->t的路径数
    std::vector<Path> paths;

    std::priority_queue<Path, std::vector<Path>, std::greater<Path>> pq;
    Path p(s);
    pq.push(p);

    while (!pq.empty() && cnt < k)
    {
        Path currPath = pq.top();
        pq.pop();

        int v = currPath.getLastVertice();

        for (auto e : g.adj(v))
        {
            int w = e.to();
            if (!currPath.contains(w))
            {
                Path newPath(currPath, e);
                if (w == t)
                {
                    paths.push_back(newPath);
                    ++cnt;
                }
                pq.push(newPath);
            }
        }
    }
    return paths;
}

std::vector<DirectedEdge> DijkstraSecondSP(WeightedDigraph &g, int s, int t, int k)
{
    std::vector<Path> paths = KShortestPaths(g, s, t, k);

    std::vector<DirectedEdge> ret;

    if (paths.size() == k)
        ret = paths[k - 1].getPath();
    return ret;
}
