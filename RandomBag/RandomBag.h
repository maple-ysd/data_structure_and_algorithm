#ifndef RANDOMBAG_H_
#define RANDOMBAG_H_
// 背包，实现每次遍历时，N！可能的结果出现的概率相等
#include <iostream>
#include <random>
template <typename T>
class RandomBag
{
public:
    RandomBag();
    ~RandomBag();
    bool isEmpty() { return count == 0; }
    int size() { return count; }
    void add(const T &item);
    T* begin() { randomShuffle(); return data; }
    T* end() { return data + count; }
private:
    void randomShuffle();
    void resize(int sz);
    T *data;
    int count = 0;
    int capacity;

};

template <typename T>
RandomBag<T>::RandomBag():count(0), capacity(1)
{
    data = new T[capacity];
    if (!data)
    {
        std::cout << "memory allocation in RandomBag construction failed\n";
        std::exit(EXIT_FAILURE);
    }
}

template <typename T>
RandomBag<T>::~RandomBag()
{
    delete data;
}

template <typename T>
void RandomBag<T>::add(const T &item)
{
    if (count == capacity)
        resize(capacity * 2);
    data[count] = item;
    ++count;
}

template <typename T>
void RandomBag<T>::resize(int sz)
{
    T *temp = data;
    data = new T[sz];
    for (int i = 0; i < count; ++i)
        data[i] = temp[i];
    delete temp;
}

template <typename T>
void RandomBag<T>::randomShuffle()
{
    static std::default_random_engine e;
    std::uniform_int_distribution<int> u(0, count - 1);
    for (int i = 0; i < count; ++i)
    {
        T temp = data[i];
        int j = u(e);
        data[i] = data[j];
        data[j] = temp;
    }
}
#endif // RANDOMBAG_H_
