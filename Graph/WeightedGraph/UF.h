#ifndef UF_H_
#define UF_H_

class UF
{
public:
    UF(int N);
    ~UF() { delete[] id; delete[] sz; }
    bool connected(int v, int w) { return id[v] == id[w]; }
    int find(int v);        // 找该连通分量的id
    void Union(int v, int w);
    int count() { return cnt; }
private:
    int *id;        // 可视为指向根节点或双亲节点
    int *sz;        // 每一棵树代表一个连通分量，sz表示其连通分量里的顶点个数
    int cnt;


};

#endif // UF_H_
