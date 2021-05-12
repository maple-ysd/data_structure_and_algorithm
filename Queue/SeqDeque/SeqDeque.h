#ifndef SEQDEQUE_H_
#define SEQDEQUE_H_

// 用动态数组实现支持两端插入删除的deque, 同时支持数组大小的动态调整
#include <iostream>
template <typename T>
class SeqDeque
{
public:
    SeqDeque();
    ~SeqDeque();
    bool isEmpty() { return first == last; }
    int size() { return last - first; }
    void pushLeft(const T &item);
    void pushRight(const T &item);
    T popLeft();
    T popRight();
    void print();
private:
    void resize(int sz);
    T *data;
    int first;      // pointing to first element
    int last;       // pointing to the one past end
    int capacity = 2;
};

template <typename T>
SeqDeque<T>::SeqDeque(): capacity(2)
{
    data = new T[capacity];
    if (!data)
    {
        std::cout << "memory allocation in construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    first = last = capacity / 2;
}
template <typename T>
SeqDeque<T>::~SeqDeque()
{
    delete data;
}

template <typename T>
void SeqDeque<T>::pushLeft(const T &item)
{
    if (first == 0)
        resize(capacity * 2);       // shift items to center
    data[--first] = item;
}
template <typename T>
void SeqDeque<T>::pushRight(const T &item)
{
    if (last == capacity)
        resize(capacity * 2);       // shift items to center
    data[last++] = item;
}
template <typename T>
T SeqDeque<T>::popLeft()
{
    if (isEmpty())
    {
        std::cout << "SeqDeque is empty, popLeft operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    T t = data[first++];
    if (size() == capacity / 4)
        resize(capacity / 2);       // shift items to center
    return t;
}
template <typename T>
T SeqDeque<T>::popRight()
{
    if (isEmpty())
    {
        std::cout << "SeqDeque is empty, popRight operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    T t = data[--last];
    if (size() == capacity / 4)
        resize(capacity / 2);       // shift items to center
    return t;
}

template <typename T>
void SeqDeque<T>::print()
{
    if (isEmpty())
    {
        std::cout << "SeqDeque is empty.\n";
    }
    else
        {
            int i = first;
//            std::cout << capacity << ": ";
            while (i < last)
            {
                std::cout << data[i++] << " ";
            }
        }
}

template <typename T>
void SeqDeque<T>::resize(int sz)
{
    if (sz == 1)
    {
        first = last = 1;       // keep the minimum capacity equal to 2
        return;
    }
    int start = sz / 2 - size() / 2;
    T *temp = data;
    data = new T[sz];
    if (!data)
    {
        std::cout << "memory allocation in resize operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    int j = start;
    for (int i = first; i < last; ++i)
        data[j++] = temp[i];
    first = start;
    last = j;
    capacity = sz;
    delete temp;
}

#endif // SEQDEQUE_H_
