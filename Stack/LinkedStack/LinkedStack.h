#ifndef LINKEDSTACK_H_
#define LINKEDSTACK_H_

#include <iostream>
// linked stack push new node in the beginning instead of end
template <typename T>
class LinkedStack
{
    struct Node
    {
        T data;
        Node *next;
    };
public:
    LinkedStack();    // create an empty linked stack with only head node
    ~LinkedStack();
    bool empty() { return head->next == nullptr; }
    T getTop();
    void push(const T &item);
    void pop();
private:
    Node *head;         // always pointing to head node and push new node after this node
};

template <typename T>
LinkedStack<T>::LinkedStack()
{
    head = new Node;
    if (head == nullptr)
    {
        std::cout << "memory allocation failure.\n";
        std::exit(EXIT_FAILURE);
    }
    head->next = nullptr;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    while (head->next)          // free all the nodes except head node
    {
        Node *temp = head->next;
        head->next = temp->next;
        delete temp;
    }
    delete head;                // free head node
}

template <typename T>
T LinkedStack<T>::getTop()
{
    if (head->next == nullptr)
    {
        std::cout << "empty stack, getTop operation fails.\n";
        std::exit(EXIT_FAILURE);
    }
    return head->next->data;
}

template <typename T>
void LinkedStack<T>::push(const T &item)
{
    Node *pnew = new Node;
    if (pnew == nullptr)
    {
        std::cout << "memory allocation failure.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = item;
    pnew->next = head->next;
    head->next = pnew;
}

template <typename T>
void LinkedStack<T>::pop()
{
    if (head->next == nullptr)
    {
        std::cout << "empty stack, pop operation fails\n";
        std::exit(EXIT_FAILURE);
    }
    Node *temp = head->next;
    head->next = temp->next;
    delete temp;
}

#endif // LINKEDSTACK_H_
