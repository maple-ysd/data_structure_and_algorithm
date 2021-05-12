#ifndef UF_H_
#define UF_H_

class UF
{
public:
    UF(int N);
    ~UF() { delete[] id; delete[] sz; }
    bool connected(int v, int w) { return id[v] == id[w]; }
    int find(int v);        // �Ҹ���ͨ������id
    void Union(int v, int w);
    int count() { return cnt; }
private:
    int *id;        // ����Ϊָ����ڵ��˫�׽ڵ�
    int *sz;        // ÿһ��������һ����ͨ������sz��ʾ����ͨ������Ķ������
    int cnt;


};

#endif // UF_H_
