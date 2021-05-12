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
//    std::cout << "��ӡ·�� bfs 4->6:\n";
//    BreadFirstPath b(g, 4);
//    b.printPathTo(6);
//    cout << endl;
//
//    //
//    cout << "��ӡ4���ڵ���ͨ�����ﶥ��ĸ���:\n";
//    DepthFirstSearch d(g, 4);
//    cout << d.count() << endl;
//    //
//    cout << "��ӡ·�� dfs 4->6:\n";
//    DepthFirstPath dp(g, 4);
//    dp.printPathTo(6);
//
//    // ����DFS��������ͨ����
//    cout << "��ͨ����������DFS��:\n";
//    ConnectedComponentsIterativeDFS cc1(g);
//    cout << cc1.count() << endl;
//
//    // �ݹ�DFS��������ͨ����
//    cout << "��ͨ�������ݹ�DFS��:\n";
//    ConnectedComponentsRecursiveDFS cc2(g);
//    cout << cc2.count() << endl;
//
//    // �ݹ�DFS, �ж��Ƿ��л�
//    cout << "�Ƿ��л�:\n";
//    Cycle c(g);
//    cout << boolalpha << c.HasCycle() << noboolalpha << endl;
//
//    // �Ƿ�Ϊ2��ͼ
//    cout << "�Ƿ���֣�\n";
//    TwoColors tc(g);
//    cout << tc.isBipartite() << endl;

    //
    SymbolGraph sg("test.txt");
    sg.print();
    sg.DegreesOfSeparation("sheep", "grass");
    return 0;
}
