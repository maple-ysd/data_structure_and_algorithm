#ifndef SYMBOLGRAPH_H_
#define SYMBOLGRAPH_H_
/** 符号图
 */

#include <iostream>
#include <fstream>
#include "Graph.h"
#include <string>
#include <stack>
#include <unordered_map>
#include <sstream>
#include "BreadFirstPath.h"
class SymbolGraph
{
public:
    // 默认(从文件里读)空白分割, 如下，第一个数代表起始位置，后面的代表邻接点
    // 1 2 3 4 5 6
    // 2 3 4 5
    // 3 4
    // 5 6
    SymbolGraph(std::string file)
    {
        std::ifstream fin(file);
        // 建立字符串与数字的映射与反映射
        std::string line;
        std::string vex;
        while (std::getline(fin, line))
        {
            std::istringstream record(line);
            while (record >> vex)
            {
                if (vexToNumMap.find(vex) == vexToNumMap.end())
                    vexToNumMap.insert(std::make_pair(vex, vexToNumMap.size()));
            }
        }
        keys = new std::string[vexToNumMap.size()];
        for (auto v : vexToNumMap)
             keys[v.second] = v.first;
        fin.close();

        fin.open(file);
        // 建图
        pg = new Graph(vexToNumMap.size());
        std::string vex1, vex2;
        while (std::getline(fin, line))
        {
            std::istringstream record(line);
            if (!(record >> vex1)) continue;
            while (record >> vex2)
            {
                pg->addEdge(vexToNumMap[vex1], vexToNumMap[vex2]);
            }
        }
        fin.close();
    }
    ~SymbolGraph()
    {
        delete[] keys;
    }
    bool contains(std::string vex) { return vexToNumMap.find(vex) != vexToNumMap.end(); }
    int index(std::string vex) { return vexToNumMap.at(vex); }
    std::string vertex(int index) { return keys[index]; }

    void print()
    {
        for (auto x : vexToNumMap)
        {
            std::cout << x.first << ": ";
            for (auto v : pg->getAdjacentList(x.second))
                std::cout << keys[v] << " ";
            std::cout << std::endl;
        }
    }

    /**< 间隔的度 (调用bfs)*/
    void DegreesOfSeparation(std::string from, std::string to)
    {
        int vex1 = vexToNumMap[from];
        int vex2 = vexToNumMap[to];
        BreadFirstPath b(*pg, vex1);
        std::stack<int> s = b.getPathTo(vex2);
        std::cout << from << "->" << to << std::endl;
        while (!s.empty())
        {
            std::cout << "    " << keys[s.top()] << std::endl;
            s.pop();
        }
    }

private:
    std::unordered_map<std::string, int> vexToNumMap;
    std::string *keys;
    Graph *pg = nullptr;
};




#endif // SYMBOLGRAPH_H_
