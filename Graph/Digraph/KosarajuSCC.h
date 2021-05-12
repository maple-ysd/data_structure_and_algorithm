#ifndef KOSARAJUSCC_H_
#define KOSARAJUSCC_H_

#include "Digraph.h"

class KosarajuSCC
{
public:
    KosarajuSCC(Digraph &g);
    ~KosarajuSCC() { delete[] visited; delete[] id;}
    bool stronglyConnected(int v, int w) { return id[v] == id[w]; }
    int getID(int v) { return id[v]; }
    int count() { return cnt; }
private:
    void dfs(Digraph &g, int v);
    bool *visited;
    int *id;
    int cnt;
} ;

#endif // KOSARAJUSCC_H_
