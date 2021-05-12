#ifndef WEIGHTEDQUICKUNIONCOMPRESSION_H_
#define WEIGHTEDQUICKUNIONCOMPRESSION_H_

#include <iostream>
class WeightedQuickUnionCompression
{
public:
    WeightedQuickUnionCompression(int n);
    ~WeightedQuickUnionCompression() { delete arr; delete weight; }
    int count() { return sz; }
    bool connected(int p, int q) { return find(p) == find(q); }
    int find(int p);
    void Union(int p, int q);
private:
    int *arr;
    int sz;     // 连通分量个数
    int *weight;    // 森林节点个数
};

WeightedQuickUnionCompression::WeightedQuickUnionCompression(int n)
{
    if (n <= 0)
    {
        std::cout << "the number of connected components in WeightedQuickUnionCompression must be positive.\n";
        std::exit(EXIT_FAILURE);
    }
    arr = new int[n];
    weight = new int[n];
    if (!arr || !weight)
    {
        std::cout << "memory allocation in WeightedQuickUnionCompression construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i)
    {
        arr[i] = i;
        weight[i] = 1;
    }
    sz = n;
}

int WeightedQuickUnionCompression::find(int p)
{
    if (p == arr[p])
        return p;
    return arr[p] = find(arr[p]);
}
void WeightedQuickUnionCompression::Union(int p, int q)
{
    int fp = find(p);
    int fq = find(q);
    if (fp == fq) return;
    if (weight[fp] < weight[fq])
    {
        arr[fp] = fq;
        weight[fq] += weight[fp];
    }
    else
    {
        arr[fq] = fp;
        weight[fp] += weight[fq];
    }
    --sz;
}

#endif // WEIGHTEDQUICKUNIONCOMPRESSION_H_
