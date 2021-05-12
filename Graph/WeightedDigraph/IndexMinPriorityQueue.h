#ifndef INDEXMINPRIORITYQUEUE_H_
#define INDEXMINPRIORITYQUEUE_H_

#include <vector>

class IndexMinPriorityQueue
{
public:
    IndexMinPriorityQueue(int N);
    bool contains(int v) { return qp[v]; }
    bool empty() { return cnt == 0; }
    void insert(int w, double distToW);
    void change(int w, double distToW);
    int deleteMin();
private:
    void swap(int i, int j);
    void swim(int k);
    void sink(int k);
    std::vector<double> arr;
    std::vector<int> pq;
    std::vector<int> qp;        // qp[] 为0表示元素不存在
    int cnt;
};

#endif // INDEXMINPRIORITYQUEUE_H_
