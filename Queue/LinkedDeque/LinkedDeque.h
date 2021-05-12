#ifndef LINKEDDEQUE_H_
#define LINKEDDEQUE_H_

#include <iostream>
// ������ò���ͷ�ڵ�ķ�ѭ��˫������ʵ�����˲���ɾ������,��Ҫ����ָ��ֱ�ָ���һ���ڵ�����һ���ڵ�;
// Ҳ���Բ���(��һ��ͷ�ڵ��)˫��ѭ������ʵ��, ������ֻ��Ҫһ��ָ����Ϊ��ھ���
template <typename T>
class LinkedDeque
{
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };
public:
    bool isEmpty() { return count == 0; }
    int size() { return count; }
    void pushLeft(const T &item);
    void pushRight(const T &item);
    T popLeft();
    T popRight();
    void print();
private:
    Node *first = nullptr;        // pointing to first node
    Node *last = nullptr;         // pointing to last node
    int count = 0;
};

template <typename T>
void LinkedDeque<T>::pushLeft(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in pushLeft operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    pnew->next = first;
    pnew->prev = nullptr;

    if (count == 0)
    {
        first = pnew;
        last = pnew;
    }
    else
    {
        first->prev = pnew;
        first = pnew;
    }
    ++count;
}

template <typename T>
void LinkedDeque<T>::pushRight(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in pushRight operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    pnew->next = nullptr;
    pnew->prev = last;

    if (count == 0)
    {
        first = last = pnew;
    }
    else
    {
        last->next = pnew;
        last = pnew;
    }
    ++count;
}

template <typename T>
T LinkedDeque<T>::popLeft()
{
    if (count == 0)
    {
        std::cout << "LinkedDeque is empty, popLeft operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = first;
    T t = temp->data;
    first = first->next;
    if (count == 1)
        last = nullptr;
    else
        first->prev = nullptr;
    delete temp;
    --count;
    return t;
}

template <typename T>
T LinkedDeque<T>::popRight()
{
    if (count == 0)
    {
        std::cout << "LinkedDeque is empty, popRight operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = last;
    T t = temp->data;
    last = last->prev;
    if (count == 1)
        first = nullptr;
    else
        last->next = nullptr;
    delete temp;
    --count;
    return t;
}

template <typename T>
void LinkedDeque<T>::print()
{
    if (count == 0)
        std::cout << "LinkedDeque is empty.\n";
    Node *it = first;
    while (it)
    {
        std::cout << it->data << " ";
        it = it->next;
    }
}
#endif // LINKEDDEQUE_H_
