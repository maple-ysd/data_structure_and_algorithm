#ifndef QUICKUNIONCOMPRESSION_H_
#define QUICKUNIONCOMPRESSION_H_

#include <iostream>
class QuickUnionCompression
{
public:
    QuickUnionCompression(int n);
    ~QuickUnionCompression() { delete arr; }
    int count() { return sz; }
    int find(int p);
    bool connected(int p, int q) { return find(p) == find(q); }
    void Union(int p, int q);
private:
    int *arr;
    int sz;         // 连通分量个数
};

QuickUnionCompression::QuickUnionCompression(int n)
{
    if (n <= 0)
    {
        std::cout << "The number of connected components in QuickUnionCompression construction must be  positive.\n";
        std::exit(EXIT_FAILURE);
    }
    arr = new int[n];
    if (!arr)
    {
        std::cout << "meomory allocation in QuickUnionCompression construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i)
        arr[i] = i;
    sz = n;
}
// amortized O(lgn)
int QuickUnionCompression::find(int p)
{
    if (p == arr[p])
        return p;
    return arr[p] = find(arr[p]);
}

void QuickUnionCompression::Union(int p, int q)
{
    int fp = find(p);
    int fq = find(q);
    if (fp == fq) return;
    arr[fp] = fq;
    --sz;
}

#endif // QUICKUNIONCOMPRESSION_H_
