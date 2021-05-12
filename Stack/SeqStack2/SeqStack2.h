#ifndef SEQSTACK2_H_
#define SEQSTACK2_H_

#include <iostream>
// sequence stack with dynamic memory allocation
template <typename T>
class SeqStack2
{
public:
    SeqStack2(int sz = 10): capacity(sz) { data = new T[capacity]; if (data == nullptr) { std::cerr << "memory allocation failure.\n"; std::exit(EXIT_FAILURE); } }
    ~SeqStack2() { delete data; }
    bool empty() { return top == -1; }
    int size() { return top + 1; }
    T getTop();
    void push(const T &item);
    void pop();
private:
    T *data;
    int top = -1;
    int capacity = 10;      // default
};

template <typename T>
T SeqStack2<T>::getTop()
{
    if (top == -1)
    {
        std::cout << "empty stack, can not getTop.\n";
        std::exit(EXIT_FAILURE);
    }
    return data[top];
}

template <typename T>
void SeqStack2<T>::push(const T &item)
{
    if (top == capacity - 1)
    {
        std::cout << "full stack, can not push.\n";
        std::exit(EXIT_FAILURE);
    }
    data[++top] = item;
}

template <typename T>
void SeqStack2<T>::pop()
{
    if (top == -1)
    {
        std::cout << "empty stack, can not pop.\n";
        std::exit(EXIT_FAILURE);
    }
    --top;
}


#endif // SEQSTACK2_H_
