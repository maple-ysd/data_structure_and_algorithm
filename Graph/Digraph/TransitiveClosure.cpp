#include "TransitiveClosure.h"

TransitiveClosure::TransitiveClosure(Digraph &g)
{
    vexNum = g.vertices();
    all = new DirectedDFS *[g.vertices()];

    for (int v = 0; v < g.vertices(); ++v)
        all[v] = new DirectedDFS(g, v);
}

TransitiveClosure::~TransitiveClosure()
{
    for (int v = 0; v < vexNum; ++v)
        delete all[v];
    delete[] all;
}
