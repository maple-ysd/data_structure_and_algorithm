#include <iostream>
#include <fstream>
#include "Graph.h"
#include "BreadFirstPath.h"
#include "DepthFirstSearch.h"
#include "DepthFirstPath.h"
#include "ConnectedComponentsIterativeDFS.h"
#include "ConnectedComponentsRecursiveDFS.h"
#include "Cycle.h"
#include "TwoColors.h"
#include "SymbolGraph.h"
using namespace std;

int main()
{
//    // Graph test
//    /*
//    7 10
//    1 2
//    1 3
//    1 4
//    1 5
//    1 6
//    2 3
//    2 4
//    2 5
//    3 4
//    5 6
//    */
//    Graph g(cin);
//    g.print();
//    cout << endl;
//    // BreadFirstPath test
//    std::cout << "打印路径 bfs 4->6:\n";
//    BreadFirstPath b(g, 4);
//    b.printPathTo(6);
//    cout << endl;
//
//    //
//    cout << "打印4所在的连通分量里顶点的个数:\n";
//    DepthFirstSearch d(g, 4);
//    cout << d.count() << endl;
//    //
//    cout << "打印路径 dfs 4->6:\n";
//    DepthFirstPath dp(g, 4);
//    dp.printPathTo(6);
//
//    // 迭代DFS，计算连通分量
//    cout << "连通分量（迭代DFS）:\n";
//    ConnectedComponentsIterativeDFS cc1(g);
//    cout << cc1.count() << endl;
//
//    // 递归DFS，计算连通分量
//    cout << "连通分量（递归DFS）:\n";
//    ConnectedComponentsRecursiveDFS cc2(g);
//    cout << cc2.count() << endl;
//
//    // 递归DFS, 判断是否有环
//    cout << "是否有环:\n";
//    Cycle c(g);
//    cout << boolalpha << c.HasCycle() << noboolalpha << endl;
//
//    // 是否为2分图
//    cout << "是否二分：\n";
//    TwoColors tc(g);
//    cout << tc.isBipartite() << endl;

    //
    SymbolGraph sg("test.txt");
    sg.print();
    sg.DegreesOfSeparation("sheep", "grass");
    return 0;
}
