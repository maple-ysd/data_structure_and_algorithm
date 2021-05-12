#include <iostream>
#include <fstream>
#include "WeightedGraph.h"
#include "WeightedCycle.h"
#include "ConnectedComponentWeightedGraph.h"
#include "LazyPrimMST.h"
#include "PrimMST.h"
#include "KruskalMST.h"
using namespace std;

int main()
{
    ifstream fin("test.txt");
    // 测试加权图
    WeightedGraph wg(fin);
    wg.print();
    //
    cout << "Weighted cyclle:\n";
    WeightedCycle wc(wg);
    if (wc.hasCycle())
    {
        auto s = wc.getCycle();
        while (!s.empty())
        {
            Edge *e = s.top();
            e->print();
            s.pop();
        }
    }

    ConnectedComponentWeightedGraph ccwg(wg);
    cout << "连通分量个数： " << ccwg.count() << endl;
    //
    LazyPrimMST lpmst(wg);
    cout << "LazyPrim最小生成树：\n";
    queue<Edge*> q = lpmst.edges();
    cout << "weight: " << lpmst.getWeight() << endl;
    while (!q.empty())
    {
        q.front()->print();
        q.pop();
    }
    cout << endl;

    //
    PrimMST pmst(wg);
    cout << "PrimMST 最小生成树：\n";
    cout << pmst.getWeight() << endl;
    q = pmst.edges();
    while (!q.empty())
    {
        q.front()->print();
        q.pop();
    }
    cout << endl;

    //
    KruskalMST kmst(wg);
    q = kmst.edges();
    cout << "KruskalMST 最小生成树：\n";
    while (!q.empty())
    {
        q.front()->print();
        q.pop();
    }
    cout << endl;
    cout << "Done.\n";
    return 0;
}

