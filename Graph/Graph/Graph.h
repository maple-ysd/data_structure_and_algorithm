#ifndef GRAPH_H_
#define GRAPH_H_
/** ����ͼ���ڽӱ��ʾ��
 *  Ϊ�򻯴������ﶥ�������ֱ�ʾ
 *  �ʶ��ڽӱ�ͼ�Ϊһ������������
 */


#include <iostream>
#include "SingleList.h"

#include <string>
#include <sstream>

class Graph
{
public:
    Graph(int vex): vexNum(vex), edgeNum(0)
    {
        adjacent = new SingleList<int>[vexNum];
    }
    // ���ƹ���
    Graph(Graph &g): vexNum(g.vexNum), edgeNum(0)
    {
        adjacent = new SingleList<int>[vexNum];
        for (int v = 0; v < vexNum; ++v)
        {
            // ����û�п����ڽӱ�ĵ�������Ԫ�ص�˳����Ҫ�Ļ������ԼӸ�stack��תһ��
            for (auto x : g.getAdjacentList(v))
                addEdge(v, x);
        }
    }
    Graph(std::istream &is)
    {
        int from, to;
        is >> vexNum;
        is >> edgeNum;
        adjacent = new SingleList<int>[vexNum];
        for (int i = 0; i < edgeNum; ++i)
        {
            is >> from >> to;
            adjacent[from].add(to);
            adjacent[to].add(from);
        }
    }
    ~Graph()
    {
        delete[] adjacent;
    }

    int vertices() { return vexNum; }
    int edges() { return edgeNum; }
    void addEdge(int vex1, int vex2)
    {
        adjacent[vex1].add(vex2);
        adjacent[vex2].add(vex1);
        ++edgeNum;
    }
    SingleList<int> &getAdjacentList(int vex)
    {
        return adjacent[vex];
    }
    int degrees(int vex)
    {
        return adjacent[vex].size();
    }
    void print()
    {
        for (int i = 0; i < vexNum; ++i)
        {
            std::cout << i << ":";
            for (auto x : getAdjacentList(i))
            {
                std::cout << " " << x;
            }
            std::cout << std::endl;
        }
    }
private:
    SingleList<int> *adjacent;
    int vexNum;
    int edgeNum;
};

#endif // GRAPH_H_
