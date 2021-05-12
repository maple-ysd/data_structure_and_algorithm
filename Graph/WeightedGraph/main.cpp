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
    // ���Լ�Ȩͼ
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
    cout << "��ͨ���������� " << ccwg.count() << endl;
    //
    LazyPrimMST lpmst(wg);
    cout << "LazyPrim��С��������\n";
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
    cout << "PrimMST ��С��������\n";
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
    cout << "KruskalMST ��С��������\n";
    while (!q.empty())
    {
        q.front()->print();
        q.pop();
    }
    cout << endl;
    cout << "Done.\n";
    return 0;
}

