#ifndef WEIGHTEDQUICKUNION_H_
#define WEIGHTEDQUICKUNION_H_


#include <iostream>
class WeightedQuickUnion
{
public:
    WeightedQuickUnion(int n);
    ~WeightedQuickUnion() { delete arr; delete weight; }
    int count() { return sz; }
    bool connected(int p, int q) {  return find(p) == find(q); }
    int find(int p);
    void Union(int p, int q);
private:
    int *arr;
    int sz;             // ��ͨ��������
    int capacity;       // �����С
    int *weight;        // ɭ�ֽڵ��������������ʱ�Ƚϣ����ڵ��ٵ�ɭ�ָ��ڽڵ���ɭ����
};

WeightedQuickUnion::WeightedQuickUnion(int n)
{
    if (n <= 0)
    {
        std::cout << "the connected component in WeightedQuickUnion construction must be positive.\n";
        std::exit(EXIT_FAILURE);
    }
    arr = new int[n];
    weight = new int[n];
    if (!arr || !weight)
    {
        std::cout << "memory allocation in WeightedQuickUnion construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; ++i)
    {
        arr[i] = i;
        weight[i] = 1;
    }
    sz = capacity = n;
}

int WeightedQuickUnion::find(int p)
{
    while (p != arr[p])
        p = arr[p];
    return p;
}

// O��logn��
void WeightedQuickUnion::Union(int p, int q)
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

#endif // WEIGHTEDQUICKUNION_H_
