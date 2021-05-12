#ifndef RANDOMQUEUE_H_
#define RANDOMQUEUE_H_

// 使用一个动态数组实现一个随机队列， 通过最后一个元素与范围内一个随机的元素交换并弹出来实现随机过程
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
template <typename T>
class RandomQueue
{
public:
    RandomQueue();
    ~RandomQueue() { delete data; }
    bool isEmpty() { return index == -1; }
    int size() { return index + 1; }
    void enqueue(const T &item);
    T dequeue();        // randomly erase one element from RandomQueue and return it
    T& sample();         // randomly get one element but not erase it
    void print();       // print all of the  elements in random order
private:
    void resize(int sz);
    T *data = nullptr;
    int index = -1;     // pointing to last element
    int capacity = 1;
    static std::default_random_engine e;
};
template <typename T>
std::default_random_engine RandomQueue<T>::e;
template <typename T>
RandomQueue<T>::RandomQueue(): data(nullptr), index(-1), capacity(1)
{
    data = new T[capacity];
    if (!data)
    {
        std::cout << "memory allocation in RandomQueue construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
}
template <typename T>
void RandomQueue<T>::resize(int sz)
{
    T *temp = data;
    data = new T[sz];
    if (!data)
    {
        std::cout << "memory allocation in resize operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= index; ++i)
        data[i] = temp[i];
    capacity = sz;
    delete temp;
}
template <typename T>
void RandomQueue<T>::enqueue(const T &item)
{
    if (index == capacity - 1)
        resize(capacity * 2);
    data[++index] = item;
}
template <typename T>
T RandomQueue<T>::dequeue()
{
    if (index == -1)
    {
        std::cout << "RandomQueue is empty, dequeue operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    std::uniform_int_distribution<int> u(0, index);
    int r = u(e);
    T temp = data[r];       // element to be erased and returned
    data[r] = data[index--];
    if (index + 1 == capacity / 4)
        resize(capacity / 2);
    return temp;
}

template <typename T>
T& RandomQueue<T>::sample()
{
    if (index == -1)
    {
        std::cout << "RandomQueue is empty, dequeue operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    std::uniform_int_distribution<int> u(0, index);
    return data[u(e)];
}

template <typename T>
void RandomQueue<T>::print()
{
    T arr[n + 1];
    for (int i = 0; i <= index; ++i)
        arr[i] = data [i];
    std::random_shuffle(arr, arr + index + 1);
    for (auto x : arr)
        std::cout << x << " ";
}
#endif // RANDOMQUEUE_H_
