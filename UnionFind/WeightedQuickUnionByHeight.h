#ifndef WEIGHTEDQUICKUNIONBYHEIGHT_H_
#define WEIGHTEDQUICKUNIONBYHEIGHT_H_

#include <iostream>
class WeightedQuickUnionByHeight
{
public:
    WeightedQuickUnionByHeight(int n);
    ~WeightedQuickUnionByHeight() { delete arr; delete weight; }
    int count() { return sz; }
    bool connected(int p, int q) { return find(p) == find(q); }
    int find(int p);
    void Union(int p, int q);
private:
    int *arr;
    int sz;     // 连通分量个数
    int *weight;// 森林高度
public:
    int maxHeight;  // 最大高度
};

WeightedQuickUnionByHeight::WeightedQuickUnionByHeight(int n)
{
    if (n <= 0)
    {
        std::cout << "the number of connected components in WeightedQuickUnionByHeight construction must be positive.\n";
        std::exit(EXIT_FAILURE);
    }
    arr = new int[n];
    weight = new int[n];
    if (!arr || !weight)
    {
        std::cout << "memory allocation in WeightedQuickUnionByHeight construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i)
    {
        arr[i] = i;
        weight[i] = 0;
    }
    sz = n;
    maxHeight = 1;
}

int WeightedQuickUnionByHeight::find(int p)
{
    while (p != arr[p])
        p = arr[p];
    return p;
}

void WeightedQuickUnionByHeight::Union(int p, int q)
{
    int fp = find(p);
    int fq = find(q);
    if (fp == fq) return;
    if(weight[fp] < weight[fq])
        arr[fp] = fq;
    else if (weight[fp] > weight[fq])
        arr[fq] = fp;
    else
    {
        arr[fq] = fp;
        ++weight[fp];
    }
    if (weight[fp] > maxHeight)
    {
        maxHeight = weight[fp];
    }
    --sz;
}

#endif // WEIGHTEDQUICKUNIONBYHEIGHT_H_
