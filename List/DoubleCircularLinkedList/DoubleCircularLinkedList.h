#ifndef DOUBLECIRCULARLINKEDLIST_H_
#define DOUBLECIRCULARLINKEDLIST_H_

#include <iostream>
// double circular linked list realization with a head node
template <typename T>
class DoubleCircularLinkedList
{
public:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
    };
    DoubleCircularLinkedList();
    ~DoubleCircularLinkedList();
    void push_back(const T &item);
    void push_front(const T &item);
    void pop_back();
    void pop_front();
    void insertBefore(int index, const T &item);
    void insertAfter(int index, const T &item);
    void remove(int index);
    T front();
    T back();
    T getElem(int index);
    void print();
private:
    Node* getNode(int index);
    int count = 0;
    Node *head;
};
template <typename T>
DoubleCircularLinkedList<T>::DoubleCircularLinkedList(): count(0)
{
    head = new Node;
    if (!head)
    {
        std::cout << "memory allocation in construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    head->prev = head;
    head->next = head;
}
template <typename T>
DoubleCircularLinkedList<T>::~DoubleCircularLinkedList()
{
    while (count--)
    {
        Node *temp = head->next;
        head->next = temp->next;
        delete temp;
    }
    delete head;
}
template <typename T>
void DoubleCircularLinkedList<T>::push_back(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in push_back operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    // 最后一个元素与新的元素链接
    head->prev->next = pnew;
    pnew->prev = head->prev;
    // 首尾相连更新
    head->prev = pnew;
    pnew->next = head;
    ++count;
}
template <typename T>
void DoubleCircularLinkedList<T>::push_front(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in push_back operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;

    // 头结点的存在统一了插入节点的代码(无论是第一个插入的节点还是后续的节点)
    head->next->prev = pnew;
    pnew->next = head->next;

    head->next = pnew;
    pnew->prev = head;
    ++count;
}

template <typename T>
void DoubleCircularLinkedList<T>::pop_back()
{
    if (count == 0)
    {
        std::cout << "list is empty, pop_back operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = head->prev;
    temp->prev->next = head;
    head->prev = temp->prev;
    delete temp;
    --count;
}
template <typename T>
void DoubleCircularLinkedList<T>::pop_front()
{
    if (count == 0)
    {
        std::cout << "list is empty, pop_back operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = head->next;
    head->next = temp->next;
    temp->next->prev = head;
    delete temp;
    --count;
}

template <typename T>
typename DoubleCircularLinkedList<T>::Node* DoubleCircularLinkedList<T>::getNode(int index)
{
    if (index < 0 && index > count)
    {
        std::cout << "getNode operation failed. index out of bound.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *p = head;
    if (index <= count / 2)
    {
        while (index--)
          p = p->next;
    }
    else
    {
        index = count - index + 1;
        while (index--)
          p = p->prev;
    }
    return p;
}

template <typename T>
void DoubleCircularLinkedList<T>::insertBefore(int index, const T &item)
{
    Node *pnew = new Node;
    pnew->data = item;

    Node *curr = getNode(index);

    curr->prev->next = pnew;
    pnew->prev = curr->prev;

    pnew->next = curr;
    curr->prev = pnew;
    ++count;
}

template <typename T>
void DoubleCircularLinkedList<T>::insertAfter(int index, const T &item)
{
    Node *pnew = new Node;
    pnew->data = item;

    Node *curr = getNode(index);

    curr->next->prev = pnew;
    pnew->next = curr->next;

    curr->next = pnew;
    pnew->prev = curr;
    ++count;
}

template <typename T>
void DoubleCircularLinkedList<T>::remove(int index)
{
    Node *curr = getNode(index);
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    --count;
}

template <typename T>
T DoubleCircularLinkedList<T>::front()
{
    if (count > 0)
        return head->next->data;
    else
    {
        std::cout << "list is empty, front operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
}
template <typename T>
T DoubleCircularLinkedList<T>::back()
{
    if (count > 0)
        return head->prev->data;
    else
    {
        std::cout << "list is empty, back operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
}
template <typename T>
T DoubleCircularLinkedList<T>::getElem(int index)
{
    return getNode(index)->data;
}

template <typename T>
void DoubleCircularLinkedList<T>::print()
{
    Node *p = head;
    int n = count;
    while (n--)
    {
        p = p->next;
        std::cout << p->data << " ";
    }
}





#endif // DOUBLECIRCULARLINKEDLIST_H_
