#ifndef SINGLELIST_H_
#define SINGLELIST_H_

/** ʵ��һ��������
 *  ʵ�ֹ��ܣ� ���Ԫ��add, �������Сsize
 *  ����һ����ʵ�ַ�Χforѭ�������ڱ���
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
    // ���ﲻ���ǿ��������븳ֵ

    int size() { return Size; }
    void add(T t)
    {
        Node *temp = new Node(t, first);
        first = temp;
    }
    // ����һ�����������ڷ�Χforѭ������
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
