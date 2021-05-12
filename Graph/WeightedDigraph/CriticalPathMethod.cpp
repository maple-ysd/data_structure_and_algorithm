#include "WeightedDigraph.h"
#include "AcyclicLP.h"
#include <fstream>
#include <sstream>

void CriticalPathMethod(std::string filename)
{
    int N;
    std::ifstream fin(filename);
    fin >> N;
    WeightedDigraph g(2 * N + 2);
    int s = 2 * N;
    int t = 2 * N + 1;
    std::string discard;
    getline(fin, discard);  // ´¦Àí»»ÐÐ·û
    for (int i = 0; i < N; ++i)
    {
        std::string line;
        getline(fin, line);
        std::istringstream record(line);
        double duration;
        record >> duration;
        g.addEdge(DirectedEdge(i, i + N, duration));
        g.addEdge(DirectedEdge(s, i, 0.0));
        g.addEdge(DirectedEdge(i + N, t, 0.0));

        int successor;
        while (record >> successor)
        {
            g.addEdge(DirectedEdge(i + N, successor, 0.0));
        }
    }

    AcyclicLP alp(g, s);

    std::cout << "start time:\n";
    for (int i = 0; i < N; ++i)
        std::cout << i << ":  " << alp.getDistTo(i) << std::endl;
    std::cout << "finish time:\n";
    std::cout << alp.getDistTo(t) << std::endl;
}
