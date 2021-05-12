#ifndef SEPARATECHAININGHASHTABLEFIXEDSIZE_H_
#define SEPARATECHAININGHASHTABLEFIXEDSIZE_H_

#include <functional>   // for hash模板类

template <typename Key, typename Value>
class separateChainingHashTableFixedSize
{
    struct Node
    {
        Key key;
        Value value;
        Node *next;
        Node(Key k, Value v, Node *pn): key(k), value(v), next(pn) {}
    };
    class sequentialSearchST
    {
    public:
        sequentialSearchST(): first(nullptr), Size(0) {}
        ~sequentialSearchST()
        {
            Node *temp = nullptr;
            while (first)
            {
                temp = first;
                first = first->next;
                delete temp;
            }
        }

        bool empty() { return Size == 0; }
        int size() { return Size; }
        Node *find(Key k)
        {
            Node *it = nullptr;
            for (it = first; it != nullptr; it = it->next)
                if (it->key == k) break;
            return it;
        }
        void insert(Key k, Value v)
        {
            for (Node *it = first; it != nullptr; it = it->next)
                if (it->key == k)
                {
                    it->value = v;
                    return;
                }
            first = new Node(k, v, first);
            ++Size;
        }
        void Delete(Key k)
        {
            if (first == nullptr) return;

            if (first->key == k)
            {
                Node *temp = first;
                first = first->next;
                --Size;
                delete temp;
                return;
            }
            for (Node *it = first; it != nullptr; it = it->next)
            {
                if (it->next && it->next->key == k)
                {
                    Node *temp = it->next;
                    it->next = it->next->next;
                    --Size;
                    delete temp;
                    return;
                }
            }
        }
        // 定义一个遍历的迭代器类
        class iter
        {
        private:
            Node *node;
        public:
            iter(Node *p): node(p) {}
            void operator++() { node = node->next; }
            Node &operator*() { return *node; }
            void operator=(iter rhs) { node = rhs.node; }
            bool operator==(iter rhs) { return node == rhs.node; }
            bool operator!=(iter rhs) { return node != rhs.node; }
        };
        iter begin() { return iter(first); }
        iter end() { return iter(nullptr); }
    private:
        Node *first;
        int Size;
    };


public:
    separateChainingHashTableFixedSize(): separateChainingHashTableFixedSize(997) {}
    separateChainingHashTableFixedSize(int sz)
    {
        Size = sz;
        keySize = 0;
        st = new sequentialSearchST[sz];
        for (int i = 0; i < sz; ++i)
            st[i] = sequentialSearchST();
    }
    ~separateChainingHashTableFixedSize()
    {
        delete[] st;
    }

    int size() { return keySize; }
    bool empty() { return keySize == 0; }
    int hash(Key k)
    {
        return std::hash<Key>()(k) * 31 % Size;
    }
    Node *find(Key k)
    {
        return st[hash(k)].find(k);
    }
    void insert(Key k, Value v)
    {
        int hashIndex = hash(k);
        int currentSize = st[hashIndex].size();
        st[hashIndex].insert(k, v);

        if (currentSize < st[hashIndex].size())
            ++keySize;
    }
    void Delete(Key k)
    {
        if (empty() || find(k) == nullptr) return;

        st[hash(k)].Delete(k);
        --keySize;
    }
private:
    int Size;
    int keySize;
    sequentialSearchST *st;

};

#endif // SEPARATECHAININGHASHTABLEFIXEDSIZE_H_
