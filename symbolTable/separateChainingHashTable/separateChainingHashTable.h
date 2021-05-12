#ifndef SEPARATECHAININGHASHTABLE_H_
#define SEPARATECHAININGHASHTABLE_H_

#include <functional>   // for std::hash模板类
#include <cmath>    // for std::log2()

template <typename Key, typename Value>
class separateChainingHashTable
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
            {
                if (it->key == k)
                {
                    it->value = v;
                    return;
                }
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
        // 定义一个遍历的迭代器类(加上begin(), end(),适用于范围for循环)
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
    separateChainingHashTable():separateChainingHashTable(997, 5) {}
    separateChainingHashTable(int initialSize, int initialAverageListSize)
    {
        Size = initialSize;
        averageListSize = initialAverageListSize;
        keySize = 0;
        st = new sequentialSearchST[Size];
        lgM = log2(Size);
    }
    ~separateChainingHashTable()
    {
        delete[] st;
    }

    int size() { return keySize; }
    bool empty() { return keySize == 0; }
    int hash(Key k)
    {
        int h = std::hash<Key>()(k);
        if (lgM < 26)
            h = h % PRIMES[lgM + 5];
        return h % Size;
    }
    double loadFactor()
    {
        return 1.0 * keySize / Size;
    }
    Node *find(Key k)
    {
        return st[hash(k)].find(k);
    }
    void insert(Key k, Value v)
    {
        if (loadFactor() >= averageListSize)
        {
            ++lgM;
            resize(Size * 2);
        }

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

        if (Size > 1 && loadFactor() <= 1.0 * averageListSize / 4)
        {
            --lgM;
            resize(Size / 2);
        }
    }
private:
    void resize(int newSize)
    {
        int oldSize = Size;
        Size = newSize;

        sequentialSearchST *temp = new sequentialSearchST[newSize];
        for (int i = 0; i < oldSize; ++i)
        {
            for (auto node : st[i])
                temp[hash(node.key)].insert(node.key, node.value);
        }
        delete[] st;
        st = temp;
    }
    int averageListSize;    // 平均顺序表长度
    int Size;       // 表示多少条顺序表
    int keySize;
    sequentialSearchST *st;
    int lgM;
    // 小于2的幂次的最大质数 < 2^i  i从0->31(前面的两项不符合)
    // 主要用于均匀动态调整大小后，均匀的散列
    static const int PRIMES[32];
};

template <typename Key, typename Value>
const int separateChainingHashTable<Key, Value>::PRIMES[32] = {
        1, 1, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381,
        32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301,
        8388593, 16777213, 33554393, 67108859, 134217689, 268435399,
        536870909, 1073741789, 2147483647
    };
#endif // SEPARATECHAININGHASHTABLE_H_
