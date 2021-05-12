#ifndef STEQUE_H_
#define STEQUE_H_

// 以栈为目标的队列， 支持pop, push, enque 操作，这里以双向链表(非循环)实现(为了熟悉双向链表的操作)，当然单链表也完全可以(不支持尾部删除)

#include <iostream>

template <typename T>
class Steque
{
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };
public:
    Steque();
    ~Steque();
    bool empty() { return count == 0; }
    int size() { return count; }
    void push(const T &item);
    void pop();
    void enque(const T &item);
    T front();
    T back();
    void print();
private:
    Node *first;    // pointing to head node
    Node *last;     // pointing to last node.
    int count = 0;
};

template <typename T>
Steque<T>::Steque(): count(0)
{
    first = new Node;
    if (!first)
    {
        std::cout << "memory allocation in construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    first->prev = first->next = nullptr;
    last = first;
}

template <typename T>
Steque<T>::~Steque()
{
    // delete all the nodes including head nodes
    while (first)
    {
        Node *temp = first;
        first = first->next;
        delete temp;
    }
}

template <typename T>
void Steque<T>::push(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in push operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    pnew->next = first->next;
    pnew->prev = first;

    if (last == first)
        last = pnew;
    else
        first->next->prev = pnew;
    first->next = pnew;
    ++count;
}

template <typename T>
void Steque<T>::pop()
{
    if (count == 0)
    {
        std::cout << "steque is empty, pop operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = first->next;
    first->next = temp->next;

    if (count == 1)
        last = first;
    else
        temp->next->prev = first;

    delete temp;
    --count;
}

template <typename T>
void Steque<T>::enque(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in enque operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    pnew->next = nullptr;
    pnew->prev = last;
    last->next = pnew;
    last = pnew;
    ++count;
}

template <typename T>
T Steque<T>::front()
{
    if (count == 0)
    {
        std::cout << "steque is empty, front operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    return first->next->data;
}

template <typename T>
T Steque<T>::back()
{
    if (count == 0)
    {
        std::cout << "steque is empty, back operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    return last->data;
}

template <typename T>
void Steque<T>::print()
{
    if (count == 0)
        std::cout << "Steque is empty.\n";
    else
    {
        Node *p = first->next;
        while (p)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
    }
}

#endif // STEQUE_H_
