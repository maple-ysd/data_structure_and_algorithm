#include "Arbitrage.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stack>
using namespace std;

void Arbitrage(std::string filename)
{
    ifstream fin(filename);
    int N;
    fin >> N;
    fin.get();      // 处理后面的换行符

    string name[N];

    WeightedDigraph g(N);
    string line;
    for (int i = 0; i < N; ++ i)
    {
        getline(fin, line);
        istringstream record(line);
        record >> name[i];
        double rate;
        for (int j = 0; j < N; ++j)
        {
            record >> rate;
            if (rate != 1)
                g.addEdge(DirectedEdge(i, j, -1 * log(rate)));
        }
    }
    BellmanFordSP spt(g, 0);

    if (spt.hasNegativeCycle())
    {
        double stake = 1000.0;
        stack<DirectedEdge> s = spt.negativeCycle();
        while (!s.empty())
        {
            auto e = s.top();
            cout << stake << "    " << name[e.from()];
            stake *= exp(-1 * e.getWeight());
            cout << " = " << stake << name[e.to()] << endl;
            s.pop();
        }
    }
    else
        cout << "no arbitrage opportunity.\n";
}
