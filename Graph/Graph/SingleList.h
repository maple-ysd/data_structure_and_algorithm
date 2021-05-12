#ifndef SINGLELIST_H_
#define SINGLELIST_H_

template <typename T>
class SingleList
{
    struct Node
    {
        T vertex;
        Node *next;
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
    int size() { return Size; }
    // 添加临接点
    void add(T v)
    {
        Node *newNode = new Node();
        newNode->vertex = v;
        newNode->next = first;
        first = newNode;
    }

    // 定义一个迭代器，用于遍历单链表
    class iter
    {
    public:
        iter(Node *p = nullptr): it(p) {}
        void operator++() { it = it->next; }
        T operator*() { return it->vertex; }
        void operator=(iter rhs) { it = rhs.it; }
        bool operator==(iter rhs) { return it == rhs.it; }
        bool operator!=(iter rhs) { return it != rhs.it; }
        //
        bool hasNext() { return it != nullptr; }
    private:
        Node *it;
    };

    iter begin() { return iter(first); }
    iter end() { return iter(); }
private:
    Node *first;
    int Size;
};
#endif // SINGLELIST_H_
