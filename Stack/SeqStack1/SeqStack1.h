#ifndef SEQSTACK1_H_
#define SEQSTACK1_H_

#include <iostream>
// sequence stack with fixed capacity
template <typename T>
class SeqStack1
{
private:
    static const int MAX = 10;  // notice: const int MAX = 10 (without static) can not be used as member array size
    T data[MAX];
    int top;        // pointing to the top element
public:
    SeqStack1() { top = -1; }
    ~SeqStack1() {}
    bool empty() { return top == -1; }
    T getTop();
    void push(const T &item);
    void pop();
    int size() { return top + 1; }
};

template <typename T>
T SeqStack1<T>::getTop()
{
    if (top == -1)
    {
        std::cout << "empty stack.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        return data[top];
}

template <typename T>
void SeqStack1<T>::push(const T &item)
{
    if (top == MAX - 1)
    {
        std::cout << "stack is full.\n";
        std::exit(EXIT_FAILURE);
    }
    else
        data[++top] = item;
}

template <typename T>
void SeqStack1<T>::pop()
{
    if (top == -1)
    {
        std::cout << "empty stack. can not pop\n";
        std::exit(EXIT_FAILURE);
    }
    else
        --top;
}

#endif // SEQSTACK1_H_
