#ifndef TRANSITIVECLOSURE_H_
#define TRANSITIVECLOSURE_H_

#include "Digraph.h"
#include "DirectedDFS.h"

class TransitiveClosure
{
public:
    TransitiveClosure(Digraph &g);
    ~TransitiveClosure();
    bool reachable(int v, int w) { return all[v]->hasPathTo(w); }
private:
    DirectedDFS **all;
    int vexNum;
};


#endif // TRANSITIVECLOSURE_H_
