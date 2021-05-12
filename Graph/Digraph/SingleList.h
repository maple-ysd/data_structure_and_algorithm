#ifndef SINGLELIST_H_
#define SINGLELIST_H_

/** 实现一个单链表
 *  实现功能， 添加元素add, 单链表大小size
 *  另外一个是实现范围for循环，用于遍历
 */


template <typename T>
class SingleList
{
    struct Node
    {
        T data;
        Node *next;
        Node(T t, Node *pn = nullptr): data(t), next(pn) {}
    };
public:
    SingleList(): first(nullptr), Size(0) {}
    ~SingleList()
    {
        Node *temp = nullptr;
        while (first)
        {
            temp = first;
            first = first->next;
            delete temp;
        }
    }
    // 这里不考虑拷贝构造与赋值

    int size() { return Size; }
    void add(T t)
    {
        Node *temp = new Node(t, first);
        first = temp;
    }
    // 定义一个迭代器用于范围for循环迭代
    class Iter
    {
    public:
        Iter(Node *pn = nullptr): it(pn) {}
        Iter(const Iter &rhs): it(rhs.it) {}
        bool hasNext() { return it != nullptr; }

        void operator++() { it = it->next; }
        T operator*() { return it->data; }
        bool operator==(Iter rhs) { return it == rhs.it; }
        bool operator!=(Iter rhs) { return it != rhs.it; }
    private:
        Node *it;
    };
    Iter begin() { return Iter(first); }
    Iter end() { return Iter(); }
private:
    Node *first;
    int Size;
};

#endif // SINGLELIST_H_
