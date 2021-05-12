#ifndef DIRECTEDEDGE_H_
#define DIRECTEDEDGE_H_

#include <iostream>

class DirectedEdge
{
public:
    DirectedEdge(int v1, int v2, double w): vertex1(v1), vertex2(v2), weight(w) {}
    DirectedEdge():DirectedEdge(0, 0, 0) {}
    int from() { return vertex1; }
    int to() { return vertex2; }
    double getWeight() { return weight; }
    void print() { std::cout << vertex1 << "->" << vertex2 << " " << weight << "    "; }
private:
    int vertex1;
    int vertex2;
    double weight;
};

#endif // DIRECTEDEDGE_H_
