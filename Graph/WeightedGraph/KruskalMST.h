#ifndef KRUSKALMST_H_
#define KRUSKALMST_H_

#include "WeightedGraph.h"
#include <queue>

class KruskalMST
{
public:
    KruskalMST(WeightedGraph &wg);
    ~KruskalMST() {}
    std::queue<Edge*> edges() { return mst; }
private:
    std::queue<Edge*> mst;
};

#endif // KRUSKALMST_H_
