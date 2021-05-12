#include <iostream>
#include <fstream>
#include "Digraph.h"
#include "DirectedDFS.h"
#include "DepthFirstDirectedPath.h"
#include "BreadthFirstDirectedPath.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"
#include "Topological.h"
#include "KosarajuSCC.h"
#include "TransitiveClosure.h"
using namespace std;

void print(stack<int> &s)
{
    bool first = true;
    while (!s.empty())
    {
        if (first)
            first = false;
        else
            cout << "->";
        cout << s.top();
        s.pop();
    }
    cout << endl;
}

void print2(queue<int> &q)
{
    bool first = true;
    while (!q.empty())
    {
        if (first)
            first = false;
        else
            cout << "->";
        cout << q.front();
        q.pop();
    }
    cout << endl;
}

int main()
{
    //
    ifstream fin("test.txt");
    Digraph dg(fin);
    fin.close();
    dg.addEdge(4, 5);
    dg.print();

    //
    DirectedDFS ddfs(dg, 2);
    DirectedDFS ddfs2(dg, {0, 6});

    //
    DepthFirstDirectedPath dfdp(dg, 0);
    if (dfdp.hasPathTo(9))
    {
        stack<int> s = dfdp.pathTo(9);
        print(s);
    }

    //
    BreadthFirstDirectedPath bfdp(dg, 0);
    if (bfdp.hasPathTo(9))
    {
        stack<int> s = bfdp.pathTo(9);
        print(s);
    }
    //
    cout << "有向环： \n";
    DirectedCycle dc(dg);
    if (dc.hasCycle())
    {
        stack<int> s = dc.getCycle();
        print(s);
    }

    DepthFirstOrder dfo(dg);
    cout << "深度优先顺序（前序、后序、逆后序）：\n";
    queue<int> pre = dfo.preOrder();
    queue<int> post = dfo.postOrder();
    stack<int> reversePost = dfo.reversePostOrder();
    print2(pre);
    print2(post);
    print(reversePost);

    //
    cout << "拓扑排序：\n";
    Topological t(dg);
    if (t.isDAG())
    {
        stack<int> s = t.getOrder();
        print(s);
    }
    else
    {
        cout << "有环.\n";
    }

    //
    cout << "kosaraju 强连通分量：\n";
    KosarajuSCC kscc(dg);
    if (kscc.stronglyConnected(0, 4))
        cout << "0 和 4 是强连通的\n";
    cout << "强连通分量个数：\n";
    cout << kscc.count() << endl;

    //
    cout << "传递闭包：\n";
    TransitiveClosure tc(dg);
    cout << "0 -> 9 可行吗?  ";
    cout << boolalpha << tc.reachable(0, 9) << noboolalpha << endl;

    return 0;
}
