#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_

#include <iostream>

template <typename T>
class CircularQueue
{
public:
    CircularQueue(int sz = 10);
    ~CircularQueue();
    bool empty() { return front == rear; }
    int size() { return (rear - front + capacity) % capacity; }
    void push(const T &item);
    void pop();
    T getFront();
    T getBack();
private:
    T *data;
    int capacity;       // represents the array size, but can only store capacity-1 elements
    int front;          // pointing to the first element
    int rear;           // pointing to one passed end
};

template <typename T>
CircularQueue<T>::CircularQueue(int sz): capacity(sz), front(0), rear(0)
{
    data = new T[capacity];
    if (!data)
    {
        std::cout << "memory allocation in CircularQueue construction fails.\n";
        std::exit(EXIT_FAILURE);
    }
}

template <typename T>
CircularQueue<T>::~CircularQueue()
{
    if (data)
        delete data;
}

template <typename T>
void CircularQueue<T>::push(const T &item)
{
    if ((rear + 1) % capacity == front)
    {
        std::cout << "queue is full, push operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    else
    {
        data[rear] = item;
        rear = (rear + 1) % capacity;
    }
}

template <typename T>
void CircularQueue<T>::pop()
{
    if (empty())
    {
        std::cout << "queue is empty, pop operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        front = (front + 1) % capacity;
}

template <typename T>
T CircularQueue<T>::getFront()
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
T CircularQueue<T>::getBack()
{
    if (empty())
    {
        std::cout << "queue is empty, getBack operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        return data[(rear - 1 + capacity) % capacity];
}

#endif // CIRCULARQUEUE_H_
