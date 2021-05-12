#ifndef QUICKFIND_H_
#define QUICKFIND_H_

#include <iostream>

class QuickFind
{
public:
    QuickFind(int n);
    ~QuickFind() { delete arr; }
    int count() { return sz; }
    bool connected(int p, int q) { return find(p) == find(q); }
    int find(int p) { return arr[p]; }
    void Union(int p, int q);
private:
    int *arr;       //
    int sz;         // 连通分量个数
    int length;   // 数组大小
};

QuickFind::QuickFind(int n)
{
    if (n <= 0)
    {
        std::cout << "the connected components in QuickFind construction must be bigger than 0\n";
        std::exit(EXIT_FAILURE);
    }
    arr = new int[n];
    if (!arr)
    {
        std::cout << "memory allocation in QuickFind construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i)
        arr[i] = i;
    sz = n;
    length = n;
}
// O（n）
void QuickFind::Union(int p, int q)
{
    int fp = arr[p];
    int fq = arr[q];
    if (fp == fq) return;
    else
    {
        for (int i = 0; i < length; ++i)
            if (arr[i] == fp) arr[i] = fq;
    }
    --sz;
}
#endif // QUICKFIND_H_
