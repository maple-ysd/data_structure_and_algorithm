#ifndef SEQQUEUE_H_
#define SEQQUEUE_H_

#include <iostream>
template <typename T>
class SeqQueue
{
public:
    SeqQueue(int sz = 10);
    ~SeqQueue();
    bool empty() { return rear == front; }
    int size() { return rear - front; }     // get number of element
    void push(const T &item);
    void pop();
    T getFront();
    T getBack();
private:
    T *data;
    int capacity;   // array capacity
    int front;      // pointing to the first element if exist
    int rear;       // pointing to one past end

};

template <typename T>
SeqQueue<T>::SeqQueue(int sz): capacity(sz), front(0), rear(0)
{
    data = new T[capacity];
    if (!data)
    {
        std::cout << "memory allocation in SeqQueue construction fails.\n";
        std::exit(EXIT_FAILURE);
    }
}
template <typename T>
SeqQueue<T>::~SeqQueue()
{
    if (data)
        delete data;
}

template <typename T>
void SeqQueue<T>::push(const T &item)
{
    if (rear != capacity)
    {
        data[rear] = item;
        ++rear;
    }
    else
    {
        std::cout << "queue is full, push operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
}
template <typename T>
void SeqQueue<T>::pop()
{
    if (empty())
    {
        std::cout << "queue is empty, pop operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        ++front;
}

template <typename T>
T SeqQueue<T>::getFront()
{
    if (empty())
    {
        std::cout << "queue is empty, getFront operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        return data[front];
}

template <typename T>
T SeqQueue<T>::getBack()
{
    if (empty())
    {
        std::cout << "queue is empty, getBack operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        return data[rear - 1];
}

#endif // SEQQUEUE_H_
