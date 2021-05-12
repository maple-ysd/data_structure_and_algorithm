#ifndef HASHSET_H_
#define HASHSET_H_

#include <iostream>
#include <vector>
#include <cmath>            // for log2()
#include <functional>       // for std::hashƒ£∞Â¿‡

template <typename Key>
class hashSet
{
private:
    class sequentialSearchST
    {
    public:
        struct Node
        {
            Key key;
            Node *next;
            Node(Key k, Node *p): key(k), next(p) {}
        };
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
        bool contains(Key k)
        {
            for (Node *node = first; node != nullptr; node = node->next)
                if (node->key == k) return true;
            return false;
        }
        void insert(Key k)
        {
            for (Node *node = first; node != nullptr; node = node->next)
                if (node->key == k) return;
            first = new Node(k, first);
            ++Size;
        }
        void remove(Key k)
        {
            if (empty()) return;
            if (first->key == k)
            {
                Node *temp = first;
                first = first->next;
                delete temp;
                --Size;
                return;
            }
            for (Node *node = first; first != nullptr; node = node->next)
            {
                if (node->next != nullptr && node->next->key == k)
                {
                    Node *temp = node->next;
                    node->next = node->next->next;
                    delete temp;
                    --Size;
                    return;
                }
            }
        }
        std::vector<Key> keys()
        {
            std::vector<Key> v;
            for (Node *node = first; node != nullptr; node = node->next)
                v.push_back(node->key);
            return v;
        }
    private:
        Node *first;
        int Size;
    };

public:
    hashSet(): hashSet(997, 5) {}
    hashSet(int initialSize, int average)
    {
        Size = initialSize;
        averageListSize = average;
        keySize = 0;
        st = new sequentialSearchST[Size];
        lgM = log2(Size);
    }
    ~hashSet()
    {
        delete[] st;
    }
    int size() { return keySize; }
    bool empty() { return keySize == 0; }
    int hash(Key k)
    {
        int h = std::hash<Key>()(k) & 0x7fffffff;
        if (lgM < 26)
            h = h % PRIMES[lgM + 5];
        return h % Size;
    }
    double getLoadFactor() { return 1.0 * keySize / Size; }
    bool contains(Key k) { return st[hash(k)].contains(k); }
    void insert(Key k)
    {
        if (getLoadFactor() > averageListSize)
        {
            ++lgM;
            resize(2 * Size);
        }
        int h = hash(k);
        int currSize = st[h].size();
        st[h].insert(k);
        if (currSize < st[h].size())
            ++keySize;
    }
    void remove(Key k)
    {
        if (empty() || !contains(k)) return;

        st[hash(k)].remove(k);
        --keySize;

        if (Size > 1 && getLoadFactor() <= 1.0 * averageListSize / 4)
        {
            --lgM;
            resize(Size / 2);
        }
    }
    std::vector<Key> keys()
    {
        std::vector<Key> v;
        for (int i = 0; i < Size; ++i)
        {
            for (auto k : st[i].keys())
                v.push_back(k);
        }
        return v;
    }
private:
    void resize(int newSize)
    {
        sequentialSearchST *temp = st;
        int oldSize = Size;

        Size = newSize;
        st = new sequentialSearchST[Size];

        for (int i = 0; i < oldSize; ++i)
        {
            for (auto k : temp[i].keys())
                st[hash(k)].insert(k);
        }
        delete[] temp;
    }
    int averageListSize;

    int Size;
    int keySize;
    sequentialSearchST *st;
    static int PRIMES[32];
    int lgM;
};

template <typename Key>
int hashSet<Key>::PRIMES[32] =
{
    1, 1, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381,
    32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301,
    8388593, 16777213, 33554393, 67108859, 134217689, 268435399,
    536870909, 1073741789, 2147483647
};

#endif // HASHSET_H_
