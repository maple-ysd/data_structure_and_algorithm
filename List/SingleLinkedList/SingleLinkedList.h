#ifndef SINGLELINKEDLIST_H_
#define SINGLELINKEDLIST_H_

typedef int ElemType;
struct Node
{
    ElemType data;
    Node *next;
};

class SingleLinkedList
{
public:
    SingleLinkedList();         // construct a default single linked list with only head node
    ~SingleLinkedList();        // destroy head node and following nodes if exist
    void Create(int n);         // add n nodes after head node
    void Print();
    int GetLength();            // number of nodes after head node (not included)
    bool IsEmpty();
    Node *Find(ElemType e);     // if found, return a pointer pointing to it, otherwise return a nullptr
    void Insert(ElemType e, int n); // insert e in nth node
    void PushBack(ElemType e);
    void PushFront(ElemType e);
    void Clear();               // destroy all of the nodes except head node
    void PopBack();
    void PopFront();
    void Delete(int n);         // delete nth node
    void Remove(ElemType e);    // remove all the nodes with data equal to e
private:
    Node *head;                 // head node
};

SingleLinkedList::SingleLinkedList()    // create empty linked list with only head node
{
    head = new Node;
    head->next = nullptr;
}
SingleLinkedList::~SingleLinkedList()
{
    if (head->next)         // delete other nodes if exist
        Clear();
    delete head;            // delete head node
}

void SingleLinkedList::Create(int n)
{
    Node *pnew, *p;
    p = head;
    for (int i = 0; i < n; ++i)
    {
        pnew = new Node;
        std::cout << "please enter the " << i + 1 << "th number: ";
        std::cin >> pnew->data;
        pnew->next = nullptr;
        p->next = pnew;
        p = p->next;
    }
}
void SingleLinkedList::Print()
{
    if (head->next == nullptr)
        std::cout << "empty single linked list.\n";
    else
    {
        Node *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
            std::cout << p->data << " ";
        }
    }
}
int SingleLinkedList::GetLength()
{
    int count = 0;
    Node *p = head->next;
    while (p != nullptr)
    {
        ++count;
        p = p->next;
    }
    return count;
}

bool SingleLinkedList::IsEmpty()
{
    if (head->next == nullptr)
        return true;
    else
        return false;
}

Node *SingleLinkedList::Find(ElemType e)
{
    Node *p = head->next;
    while (p && p->data != e)
        p = p->next;
    if (p->data == e)
        return p;
    else
        return nullptr;
}
void SingleLinkedList::Insert(ElemType e, int n)
{
    if (n < 1 || n > GetLength() + 1)
        std::cout << "invalid insert position.\n";
    else
    {
        Node *pnew, *p;
        p = head;
        pnew = new Node;
        pnew->data = e;

        int count = 1;
        while (count < n)
        {
            p = p->next;
            ++count;
        }
        pnew->next = p->next;
        p->next = pnew;
    }
}

void SingleLinkedList::PushBack(ElemType e)
{
    Node *pnew, *p;
    pnew = new Node;
    pnew->next = nullptr;
    pnew->data = e;
    p = head;
    while (p->next != nullptr)
        p = p->next;
    p->next = pnew;

}

void SingleLinkedList::PushFront(ElemType e)
{
    Node *pnew = new Node;
    pnew->data = e;
    pnew->next = head->next;
    head->next = pnew;
}

void SingleLinkedList::PopBack()
{
    Node *ptemp, *p;
    p = head;
    if (p->next == nullptr)
        std::cout << "empty single linked list.\n";
    else
    {
        while (p->next != nullptr)
        {
            ptemp = p;
            p = p->next;
        }
        delete p;
        p = nullptr;
        ptemp->next = nullptr;
    }
}

void SingleLinkedList::PopFront()
{
    Node *p = head;
    if (p->next == nullptr)
        std::cout << "empty single linked list.\n";
    else
    {
        p = p->next;
        head->next = p->next;
        delete p;
        p = nullptr;
    }
}

void SingleLinkedList::Clear()
{
    Node *p = head->next;
    Node *ptemp;
    while (p != nullptr)
    {
        ptemp = p;
        p = p->next;
        delete ptemp;
    }
    head->next = nullptr;
}

void SingleLinkedList::Delete(int n)
{
    if (head->next == nullptr)
    {
        std::cout << "empty single linked list.\n";
        return;
    }
    Node *p = head;
    Node *pre = head;

    while (n-- && p)
    {
        pre = p;
        p = p->next;
    }
    if (p == nullptr)
        std::cout << "the nth element does not exist.\n";
    else
    {
        pre->next = p->next;
        delete p;
    }
}

void SingleLinkedList::Remove(ElemType e)
{
    Node *p = head->next;
    Node *pre= head;
    while (p)
    {
        if (p->data == e)
        {
            pre->next = p->next;
            delete p;
        }
        else
            pre = p;
        p = pre->next;
    }
}

#endif // SINGLELINKEDLIST_H_
