#ifndef KSHORTESTPATH_H_
#define KSHORTESTPATH_H_

#include "WeightedDigraph.h"
#include <vector>
#include <unordered_set>

class Path
{
public:
    Path(int v);
    Path(Path rhs, DirectedEdge e);
    bool contains(int v) { return verticesInPath.find(v) != verticesInPath.end(); }
    int getLastVertice() { return lastVertice; }
    double getWeight() { return weight; }
    std::vector<DirectedEdge> getPath() { return path; }
    bool operator>(const Path &rhs) const { return weight > rhs.weight; }
//    friend bool operator>(const Path &lhs, const Path &rhs);
private:
    std::vector<DirectedEdge> path;
    std::unordered_set<int> verticesInPath;
    int lastVertice;
    double weight;
};

//inline bool operator>(const Path &lhs, const Path &rhs) { return lhs.weight > rhs.weight; }
// KShortestPaths， 获取前K条路径
std::vector<Path> KShortestPaths(WeightedDigraph &g, int s, int t, int k);

// 选择第二小路径并返回
std::vector<DirectedEdge> DijkstraSecondSP(WeightedDigraph &g, int s, int t, int k);

#endif // KSHORTESTPATH_H_
