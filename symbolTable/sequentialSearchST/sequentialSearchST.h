#ifndef SEQUENTIALSEARCHST_H_
#define SEQUENTIALSEARCHST_H_

/*********************************************
无序链表实现符号表(附加一迭代器)
查找O（N）
插入/删除O（N）
**********************************************/

#include <stdexcept>
typedef std::string Key;
typedef int Value;

struct Node
{
    Key key;
    Value value;
    Node *next;
    // 头部插入
    Node (Key k, Value v, Node *n)
    {
        key = k;
        value = v;
        next = n;
    }
};
// 定义一个用来遍历链表的迭代器类（可应用于范围for循环）
struct Iterator
{
    Node *it;
    Iterator(Node *n) { it = n; }
    void operator++() { it = it->next; }
    Node& operator*() { return *it; }
    void operator=(Iterator that) { it = that.it; }
    bool operator==(Iterator that)
    {
        if (it == that.it) return true;
        else return false;
    }
    bool operator!=(Iterator that)
    {
        if (it != that.it) return true;
        else return false;
    }
};
class sequentialSearchST
{
public:
    ~sequentialSearchST()
    {
        while (first)
        {
            Node *temp = first;
            first = first->next;
            delete temp;
        }
    };
    bool isEmpty() { return Size == 0; }
    int size() { return Size; }
    bool contains(Key k);
    Value get(Key k);
    void put(Key k, Value v);
    void Delete(Key k);
    Iterator  begin() { return first; }
    Iterator end() { return nullptr; }
private:
    Node *first = nullptr;
    int Size = 0;
};

bool sequentialSearchST::contains(Key k)
{
    Node *it = first;
    while (it && it->key != k)
    {
        it = it->next;
    }
    if (!it)
        return false;
    else
        return true;
}
Value sequentialSearchST::get(Key k)
{
    Node *it = first;
    while (it && it->key != k)
    {
        it = it->next;
    }
    if (!it)
        throw std::invalid_argument("this key does not exist.\n");
    else
        return it->value;
}
void sequentialSearchST::put(Key k, Value v)
{
    Node *it = first;
    while (it && it->key != k)
    {
        it = it->next;
    }
    if (!it)
    {
        Node *pnew = new Node(k, v, first);
        first = pnew;
        ++Size;
    }
    else
        it->value = v;
}
void sequentialSearchST::Delete(Key k)
{
    if (isEmpty()) return;

    Node *it = first;
    Node *prev = first;
    while (it && it->key != k)
    {
        prev = it;
        it = it->next;
    }
    if (!it) return;
    else
    {
        Node *temp = it;
        prev->next = it->next;
        delete temp;
        --Size;
    }
}


#endif // SEQUENTIALSEARCHST_H_
