#include "Topological.h"
#include "DepthFirstOrder.h"
#include "DirectedCycle.h"

Topological::Topological(Digraph &g)
{
    DirectedCycle dc(g);
    if (!dc.hasCycle())
    {
        DepthFirstOrder dfo(g);
        order = dfo.reversePostOrder();
    }
}
