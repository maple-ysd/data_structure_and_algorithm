#include <iostream>
#include <fstream>
#include <stack>
#include "WeightedDigraph.h"
#include "Dijkstra.h"
#include "AcyclicSP.h"
#include "AcyclicLP.h"
#include "CriticalPathMethod.h"
#include "BellmanFordSP.h"
#include "Arbitrage.h"
#include "KShortestPath.h"
using namespace std;

void print(stack<DirectedEdge> s)
{
    while (!s.empty())
    {
        s.top().print();
        s.pop();
    }
    cout << endl;
}

int main()
{
    //
    ifstream fin("test.txt");
    WeightedDigraph g(fin);
    g.addEdge(DirectedEdge(6, 5, 1.5));
    g.print();
    g.reverse().print();
    //
    cout << "Dijksta (0->...):\n";
    Dijkstra dj(g, 0);
    for (int i = 0; i <= 7; ++i)
    {
        cout << "0->" << i << ":  ";
        if(dj.hasPathTo(i))
        {
            stack<DirectedEdge> s;
            s = dj.pathTo(i);
            print(s);
        }
    }
//    fin.close();
    //
    ifstream fin2("testAcyclic.txt");
    WeightedDigraph g2(fin2);
    //
    cout << "AcyclicSP:\n";
    AcyclicSP asp(g2, 0);
    for (int i = 0; i <= 10; ++i)
    {
        cout << "0->" << i << ":  ";
        if(asp.hasPathTo(i))
        {
            stack<DirectedEdge> s;
            s = asp.pathTo(i);
            print(s);
        }
    }

    //
    cout << "AcyclicLP:\n";
    AcyclicLP alp(g2, 0);
    for (int i = 0; i <= 10; ++i)
    {
        cout << "0->" << i << ":  ";
        if(alp.hasPathTo(i))
        {
            stack<DirectedEdge> s;
            s = alp.pathTo(i);
            print(s);
        }
    }

    //
    CriticalPathMethod("parallelTask.txt");

    //
    cout << "BellmanFordSP: \n";
    ifstream fin3("testNegativeCycle.txt");
    WeightedDigraph g3(fin3);
    BellmanFordSP bfsp(g3, 0);
    if (bfsp.hasNegativeCycle())
    {
        stack<DirectedEdge> s;
        s = bfsp.negativeCycle();
        cout << s.size() << endl;
        print(s);
    }

    //
    cout << "Arbitrage test:\n";
    Arbitrage("rate.txt");

    ifstream fin4("secondSP.txt");
    WeightedDigraph g4(fin4);

    std::vector<DirectedEdge> path = DijkstraSecondSP(g4, 0, 2, 2);
    cout << "0->2: second shortest path:\n";
    cout << path.size() << endl;
    for (auto e: path)
        e.print();
    cout << endl;

    return 0;
}
