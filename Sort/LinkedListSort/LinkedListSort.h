#ifndef LINKEDLISTSORT_H_
#define LINKEDLISTSORT_H_

/**********************************************
归并算法实现链表的自然排序
O（nlogn）
***********************************************/

#include <iostream>
#include <utility>
typedef int elemType;

struct Node
{
    elemType data;
    Node *next;
};

class LinkedListSort
{
public:
    LinkedListSort();
    ~LinkedListSort();
    bool isEmpty() { return sz == 0; }
    int count() { return sz; }
    void push(const elemType &e);
    Node* pop();
    void bottomUpSort();
    void print();
private:
    std::pair<Node*, Node*> Merge(Node *left, Node *right);
    Node *ptail;
    Node *phead;
    int sz;
};

LinkedListSort::LinkedListSort(): sz(0)
{
    phead = new Node;
    if (!phead)
    {
        std::cout << "memory allocation in LinkedListSort construction failed.\n";
        std::exit(EXIT_FAILURE);
    }
    phead->next = nullptr;
    ptail = phead;
}
LinkedListSort::~LinkedListSort()
{
    while(phead)
    {
        Node *temp = phead;
        phead = phead->next;
        delete temp;
    }
}
void LinkedListSort::push(const elemType &e)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in push operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = e;
    pnew->next = nullptr;
    ptail->next = pnew;
    ptail = pnew;
    ++sz;
}
// 两个子链表的合并，并返回合并后的首尾节点
std::pair<Node*, Node*> LinkedListSort::Merge(Node *left, Node *right)  // left right 表示两个子链表的起始位置
{
    Node *first, *last;
    if (left->data <= right->data)
    {
        first = last = left;
        left = left->next;
    }
    else
    {
        first = last = right;
        right = right->next;
    }
    while (left != nullptr && right != nullptr)
    {
        if (left->data <= right->data)
        {
            last->next = left;
            last = left;
            left = left->next;
        }
        else
        {
            last->next = right;
            last = right;
            right = right->next;
        }
    }
    while (left)
    {
        last->next = left;
        last = left;
        left = left->next;
    }
    while (right)
    {
        last->next = right;
        last = right;
        right = right->next;
    }
    return std::make_pair(first, last);
}

void LinkedListSort::bottomUpSort()
{
    if (sz <= 1) return;
    Node *lo, *mid, *hi;
    lo = phead->next;
    hi = mid = nullptr;
    Node *it = phead->next;
    bool firstTime = true;
    while (true)
    {
        if (firstTime)
            ptail = phead;
        bool firstSub = true;
        while (it && it->next)
        {
            if (it->data > it->next->data)
            {
                if (firstSub)
                {
                    mid = it;
                    firstSub = false;
                    it = it->next;
                }
                else
                {
                    hi = it;
                    it = it->next;
                    break;
                }
            }
            else
                it = it->next;
        }

        if (mid == nullptr)     // mid不为空的前提是他后面哪个节点比他本身小
        {
            if (firstTime)       // 已经有序
                break;
            else if (!firstTime)
            {
                ptail->next = lo;
                while (ptail)
                {
                    ptail = ptail->next;
                }
                // 重头再来，下一轮归并
                lo = phead->next;
                mid = hi = nullptr;
                it = phead->next;
                firstTime = true;
            }
        }
        else
        {
            Node *left, *right;
            if (hi == nullptr)
            {
                left = lo;
                right = mid->next;
                mid->next = nullptr;
                auto ret = Merge(left, right);
                ptail->next = ret.first;
                ptail = ret.second;
                // 重头再来， 下一轮归并
                lo = phead->next;
                mid = hi = nullptr;
                it = phead->next;
                firstTime = true;
            }
            else
            {
                left = lo;
                right = mid->next;
                mid->next = nullptr;
                hi->next = nullptr;
                auto ret = Merge(left, right);
                ptail->next = ret.first;
                ptail = ret.second;
                // 继续后面的归并
                lo = it;
                mid = hi = nullptr;
                firstTime = false;
            }
        }
    }
}
void LinkedListSort::print()
{
    Node *it = phead->next;
    while (it)
    {
        std::cout << it->data << " ";
        it = it->next;
    }
    std::cout << std::endl;
}
#endif // LINKEDLISTSORT_H_
