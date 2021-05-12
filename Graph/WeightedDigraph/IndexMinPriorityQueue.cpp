#include "IndexMinPriorityQueue.h"
#include <stdexcept>

IndexMinPriorityQueue::IndexMinPriorityQueue(int N): arr(N), pq(N + 1), qp(N + 1), cnt(0)
{
    // N+1是因为优先队列从1开始放，忽略位置0
    for (int i = 0; i < N + 1; ++i)
        qp[i] = 0;
}

void IndexMinPriorityQueue::swap(int i, int j)
{
    std::swap(pq[i], pq[j]);
    std::swap(qp[pq[i]], qp[pq[j]]);
}

void IndexMinPriorityQueue::swim(int i)
{
    while (i > 1 && arr[pq[i]] < arr[pq[i/2]])
    {
        swap(i, i/2);
        i = i / 2;
    }
}
void IndexMinPriorityQueue::sink(int k)
{
    while (2 * k <= cnt)
    {
        int n = 2 * k;
        if (n < cnt && arr[pq[n]] > arr[pq[n + 1]])
            n = n + 1;
        if (arr[pq[k]] > arr[pq[n]])
        {
            swap(k, n);
            k = n;
        }
        else
            break;

    }
}

void IndexMinPriorityQueue::insert(int w, double distToW)
{
    if (contains(w)) return;

    arr[w] = distToW;
    pq[++cnt] = w;
    qp[w] = cnt;
    swim(cnt);
}

void IndexMinPriorityQueue::change(int w, double distToW)
{
    if (!contains(w))
        throw std::runtime_error("such element does not exist, change operation failed.\n");
    arr[w] = distToW;
    swim(qp[w]);
    sink(qp[w]);
}

int IndexMinPriorityQueue::deleteMin()
{
    int MinElemIndex = pq[1];
    swap(1, cnt);
    qp[pq[cnt]] = 0;
    --cnt;
    sink(1);
    return MinElemIndex;
}
