#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include <iostream>
#include "SingleList.h"

// ������ֱ�������ִ�����

class Digraph
{
public:
    Digraph(int vertices);
    Digraph(std::istream &is);
    ~Digraph() { delete[] adj; }

    int vertices() { return vexNum; }
    int edges() { return edgeNum; }
    SingleList<int> &adjacent(int vex) { return adj[vex]; }

    void addEdge(int vex1, int vex2);
    // ����reverse ����һ��Ҫ�ǵ�delete
    Digraph *reverse();
    void print();
private:
    int vexNum;
    int edgeNum;
    SingleList<int> *adj;

};
#endif // DIGRAPH_H_
