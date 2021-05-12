#ifndef INDEXMINPRIORITYQUEUE_H_
#define INDEXMINPRIORITYQUEUE_H_

#include <iostream>
/********************************************
索引优先队列（最小元）
*********************************************/
typedef int elemType;
class indexMinPriorityQueue
{
public:
    indexMinPriorityQueue(int sz);      // 这里数组大小在初始化时就确定，不再动态变化
    ~indexMinPriorityQueue();
    bool empty() { return Size == 0; }
    int size() { return Size; }
    void insert(int index, elemType item);
    void change(int index, elemType item);
    int deleteMin();
    int minIndex();
    elemType minElem();
    void Delete(int index);
private:
    void swim(int index);
    void sink(int index);
    void exchange(int index1, int index2);
    elemType *data;      // 存放元素的数组，下标即为索引， i = 1， 2， 3 ...
    int *pq;        // 存放元素索引的优先队列 pq[j] = i
    int *qp;        // 存放元素索引在pq中的下标 qp[i] = j
    int MaxSize;
    int Size = 0;
};

indexMinPriorityQueue::indexMinPriorityQueue(int sz)
{
    if (sz < 1)
    {
        std::cout << "the size of indexMinPriorityQueue must be greater or at least equal to 1.\n";
        std::exit(EXIT_FAILURE);
    }
    data = new elemType[sz + 1];
    pq = new int[sz + 1];
    qp = new int[sz + 1];

    if (!data || !pq || !qp)
    {
        std::cout << "memory allocation failed in indexMinPriorityQueue construction.\n";
        std::exit(EXIT_FAILURE);
    }
    MaxSize = sz;
    Size = 0;
    for (int i = 0; i <= sz; ++i)
        qp[i] = -1;
}

indexMinPriorityQueue::~indexMinPriorityQueue()
{
    delete data;
    delete pq;
    delete qp;
}
void indexMinPriorityQueue::insert(int i, elemType item)
{
    if (qp[i] != -1)
    {
        std::cout << "already one element in index i.\n";
        std::exit(EXIT_FAILURE);
    }

    data[i] = item;
    ++Size;
    pq[Size] = i;
    qp[i] = Size;
    swim(Size);
}
void indexMinPriorityQueue::change(int index, elemType item)
{
    if (qp[index] == -1)
    {
        std::cout << "no element exists in the index, so you can not change it.\n";
        std::exit(EXIT_FAILURE);
    }
    data[index] = item;
    swim(qp[index]);
    sink(qp[index]);
}
int indexMinPriorityQueue::deleteMin()
{
    if (Size == 0)
    {
        std::cout << "already empty, deleteMin operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    int minElemIndex = pq[1];
    exchange(1, Size);
    --Size;
    sink(1);

    qp[minElemIndex] = -1;
    return minElemIndex;
}

elemType indexMinPriorityQueue::minElem()
{
    if (Size == 0)
    {
        std::cout << "empty indexMinPriorityQueue, minElem operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    return data[pq[1]];
}
int indexMinPriorityQueue::minIndex()
{
    if (Size == 0)
    {
        std::cout << "empty indexMinPriorityQueue, minIndex operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    return pq[1];
}

void indexMinPriorityQueue::Delete(int index)
{
    if (qp[index] == -1)
    {
        std::cout << "empty indexMinPriorityQueue, Delete operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    int i = qp[index];
    exchange(i, Size);
    --Size;
    swim(i);
    sink(i);
    qp[index] = -1;
}

void indexMinPriorityQueue::swim(int i)
{
    while (i / 2 >= 1 && data[pq[i]] < data[pq[i / 2]])
    {
        exchange(i, i / 2);
        i /= 2;
    }
}
void indexMinPriorityQueue::sink(int i)
{
    while (2 * i <= Size)
    {
        int j = 2 * i;
        if (j < Size && data[pq[j]] > data[pq[j + 1]])
            j += 1;
        if (data[pq[j]] >= data[pq[i]])
            break;
        exchange(i, j);
        i = j;
    }
}

void indexMinPriorityQueue::exchange(int index1, int index2)
{
    std::swap(pq[index1], pq[index2]);
    std::swap(qp[pq[index1]], qp[pq[index2]]);
}
#endif // INDEXMINPRIORITYQUEUE_H_
