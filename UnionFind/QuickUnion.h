#ifndef QUICKUNION_H_
#define QUICKUNION_H_

#include <iostream>
class QuickUnion
{
public:
    QuickUnion(int n);
    ~QuickUnion() { delete arr; }
    int count() { return sz; }
    bool connected(int p, int q) { return find(p) == find(q); }
    int find(int p);
    void Union(int p, int q);
private:
    int *arr;
    int sz;             // 连通分量个数
    int capacity;       // 数组大小
};

QuickUnion::QuickUnion(int n)
{
    if (n <= 0)
    {
        std::cout << "connected components in QuickUnion construction must be positive.\n";
        std::exit(EXIT_FAILURE);
    }
    arr = new int[n];
    if (!arr)
    {
        std::cout << "memory allocation in QuickUnion construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i)
        arr[i] = i;
    sz = capacity = n;
}

int QuickUnion::find(int p)
{
    while (p != arr[p])
        p = arr[p];
    return p;
}
void QuickUnion::Union(int p, int q)
{
    int fp = find(p);
    int fq = find(q);
    if (fp == fq) return;
    arr[fp] = fq;
    --sz;
}

#endif // QUICKUNION_H_
