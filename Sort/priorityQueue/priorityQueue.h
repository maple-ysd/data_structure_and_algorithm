#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
#include <algorithm>
/******************************************
���ȶ���
(��������������Ԫ���ȶ���)
*******************************************/

typedef int elemType;

class priorityQueue
{
public:
    priorityQueue();
    ~priorityQueue();
    bool empty() { return cnt == 0; }
    int size() { return cnt; }
    elemType top();
    void push(elemType item);
    void pop();
private:
    void resize(int sz);
    void swim(int index);
    void sink(int index);
    elemType *arr;      // arr[0] not used, starting from arr[1] ... arr[n]
    int cnt = 0;        // ��ʾ�Ѵ洢Ԫ�صĸ�����Ҳ���Ѵ洢Ԫ�ص����һ��Ԫ���±�
    int length;         // length = n;��ʾ�ܴ洢�����Ԫ�ظ�����Ҳ���ܴ洢�����һ��Ԫ�ص��±�
};

priorityQueue::priorityQueue()
{
    arr = new elemType[2];      // ����������һ��Ԫ��
    if (!arr)
    {
        std::cout << "memory allocation in priorityQueue construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    cnt = 0;
    length = 1;
}
priorityQueue::~priorityQueue()
{
    delete[] arr;
}

void priorityQueue::swim(int index)
{
    while (index / 2 >= 1 && arr[index] > arr[index / 2])
    {
        std::swap(arr[index], arr[index / 2]);
        index /= 2;
    }
}
void priorityQueue::sink(int index)
{
    while (2 * index <= cnt)
    {
        int j = 2 * index;
        if (j < cnt && arr[j] < arr[j + 1]) j++;
        if (arr[index] >= arr[j])   // �³�����
            break;
        std::swap(arr[index], arr[j]);
        index = j;
    }
}
void priorityQueue::resize(int sz)
{
    elemType *temp = new elemType[sz + 1];
    if (!temp)
    {
        std::cout << "memory allocation in resize operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    std::copy(arr + 1, arr + length + 1, temp + 1);
    delete[] arr;
    arr = temp;
    length = sz;
}
elemType priorityQueue::top()
{
    if (cnt == 0)
    {
        std::cout << "already empty, top operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        return arr[1];
}
void priorityQueue::push(elemType item)
{
    if (cnt == length)
        resize(length * 2);
    arr[++cnt] = item;
    swim(cnt);
}
void priorityQueue::pop()
{
    if (cnt == 0)
    {
        std::cout << "already empty, pop operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    std::swap(arr[1], arr[cnt--]);
    sink(1);
    if (cnt == length / 4)
        resize(length / 2);
}

#endif // PRIORITYQUEUE_H_
