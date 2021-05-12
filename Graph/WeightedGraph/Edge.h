#ifndef EDGE_H_
#define EDGE_H_

#include <stdexcept>
#include <iostream>

class Edge
{
public:
    Edge(int vex1, int vex2, double w): vertex1(vex1), vertex2(vex2), weight(w) {}
    double getWeight() { return weight; }
    int either() { return vertex1; }
    int other(int vex)
    {
        if (vex == vertex1) return vertex2;
        else if (vex == vertex2) return vertex1;
        else throw std::runtime_error("inconsistent edge.\n");
    }
    bool operator<(const Edge &rhs)
    {
        if (weight < rhs.weight) return true;
        else return false;
    }
    friend bool cmp(Edge *lhs, Edge *rhs);
    friend class Greater;
    void print()
    {
        std::cout << vertex1 << "-" << vertex2 << " " << weight << "    ";
    }
private:
    int vertex1;
    int vertex2;
    double weight;
};

bool cmp(Edge *lhs, Edge *rhs);     // 该函数没什么用，与下面的仿函数功能类似（写上只是测试一下传函数指针）
typedef bool (*Func)(Edge *lhs, Edge *rhs);
class Greater
{
public:
    bool operator()(Edge *lhs, Edge *rhs)
    {
        return lhs->weight > rhs->weight;
    }
};
#endif // EDGE_H_
