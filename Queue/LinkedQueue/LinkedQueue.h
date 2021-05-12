#ifndef LINKEDQUEUE_H_
#define LINKEDQUEUE_H_

#include <iostream>
template <typename T>
class LinkedQueue
{
    struct Node
    {
        T data;
        Node *next;
    };
public:
    LinkedQueue();
    ~LinkedQueue();
    bool empty() { return rear == front; }
    int size();
    void push(const T &item);
    void pop();
    T getFront();
    T getBack();
private:
    Node *front;        // pointing to head node (in this template class, head node is added)
    Node *rear;         // pointing to last node instead of one passed end here or head node if empty
};

template <typename T>
LinkedQueue<T>::LinkedQueue()
{
    front = new Node;
    if (!front)
    {
        std::cout << "memory allocation in LinkedQueue construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    front->next = nullptr;
    rear = front;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    // delete all the nodes including head node
    while(front)
    {
        rear = front;       // since this object is gonna destroyed, to save memory, use rear to store front instead of create a new temporary pointer;
        front = front->next;
        delete rear;
    }
}

template <typename T>
int LinkedQueue<T>::size()
{
    int count = 0;
    Node *p = front;        // do not use front variable to traverse directly because this will change the object state.
    while (p->next)
    {
        ++count;
        p = p->next;
    }
    return count;
}

template <typename T>
void LinkedQueue<T>::push(const T &item)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in push operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    pnew->next = nullptr;
    rear->next = pnew;
    rear = pnew;
}

template <typename T>
void LinkedQueue<T>::pop()
{
    if (empty())
    {
        std::cout << "queue is empty, pop operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = front->next;
    front->next = temp->next;
    delete temp;
    if (!front->next)
        rear = front;
}

template <typename T>
T LinkedQueue<T>::getFront()
{
    if (empty())
    {
        std::cout << "queue is empty, getFront operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    return front->next->data;
}

template <typename T>
T LinkedQueue<T>::getBack()
{
    if (empty())
    {
        std::cout << "queue is empty, getBack operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    return rear->data;
}
#endif // LINKEDQUEUE_H_
