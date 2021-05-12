#ifndef INDEXMINPRIORITYQUEUE_H_
#define INDEXMINPRIORITYQUEUE_H_

#include <stdexcept>
template <typename T>
class IndexMinPriorityQueue
{
public:
    IndexMinPriorityQueue(int N)
    {
        arr = new T[N + 1];
        pq = new int[N + 1];
        qp = new int[N + 1];
        sz = 0;
        cap = N + 1;
        for (int i = 0; i <= N; ++i)
            qp[i] = 0;             // 表示arr i这个位置没元素

    }
    ~IndexMinPriorityQueue()
    {
        delete[] arr;
        delete[] pq;
        delete[] qp;
    }
    bool contains(int i) { return qp[i]; }
    int size() { return sz; }
    bool empty() { return sz == 0; }
    void insert(int i, T t)
    {
        if (contains(i) || sz == cap - 1 ) return;

        arr[i] = t;
        pq[++sz] = i;
        qp[i] = sz;
        swim(sz);
    }
    void change(int i, T t)
    {
        if (!contains(i))
            throw std::runtime_error("no element exists related with index i.\n");
        arr[i] = t;

        int k = qp[i];
        swim(k);
        sink(k);
    }
    int deleteMin()
    {
        if (empty())
            throw std::runtime_error("empty index queue.\n");
        int ret = pq[1];
        swap(1, sz);
        qp[pq[sz--]] = 0;
        sink(1);
        return ret;
    }
private:
    void swim(int i)        // 这里i指的是对应的优先队列pq里的索引
    {
        while (i > 1 && arr[pq[i]] < arr[pq[i / 2]])
        {
            swap(i, i/2);
            i = i/2;
        }
    }
    void sink(int i)
    {
        while (2 * i <= sz)
        {
            int k = 2 * i;
            if (k < sz && arr[pq[k + 1]] < arr[pq[k]]) k = k + 1;
            if (arr[pq[i]] > arr[pq[k]])
            {
                swap(i, k);
                i = k;
            }
            else break;
        }
    }
    void swap(int i, int j)     // 这里的i, j含义同上
    {
        std::swap(pq[i], pq[j]);
        std::swap(qp[pq[i]], qp[pq[j]]);
    }
    T *arr;     // 原始数组
    int *pq;    // 优先队列
    int *qp;    // pq的逆映射，主要是为了能够修改原始数据后，
                // 通过qp[原始数组下标]找到器在优先队列的位置，然后调整
    int sz;     // qp数组大小
    int cap;    // 容量大小
};

#endif // INDEXMINPRIORITYQUEUE_H_
