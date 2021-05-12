#ifndef DOUBLEHASHINGHASHTABLE_H_
#define DOUBLEHASHINGHASHTABLE_H_


/** 双重哈希
 *  hash1(k) = k % tableSize;
 *  hash2(k) = k % prime   (this prime should be smaller than the tableSize)
 *  hash2 不能为0
 *  然后使用 h = hash1 + i * hash2 而不是每次+1进行试探
 *
 */

 #include <iostream>
 #include <functional>
 #include <cmath>
 #include <cassert>
template <typename Key, typename Value>
class doubleHashingHashTable
{
public:
    enum State{ EXIST, EMPTY, DELETED };
    doubleHashingHashTable(int sz)
    {
        assert(sz > 31 && sz < std::pow(2, 31));

        lgM = std::log2(sz) + 1;
        sz = PRIMES[lgM];

        keys = new Key[sz];
        values = new Value[sz];
        states = new State[sz];

        Size = sz;
        keySize = 0;

        for (int i = 0; i < Size; ++i)
            states[i] = EMPTY;
    }
    ~doubleHashingHashTable()
    {
        delete[] keys;
        delete[] values;
        delete[] states;
    }

    bool empty() { return keySize == 0; }
    int size() { return keySize; }
    int hash1(Key k)
    {
        return std::hash<Key>()(k) % Size;
    }
    int hash2(Key k)
    {
        return PRIMES[lgM - 5] - std::hash<Key>()(k) % PRIMES[lgM - 5];
    }
    // 查找 找到了就返回下标，找不到就返回-1
    int find(Key k)
    {
        for (int h = hash1(k); states[h] != EMPTY; h = (h + hash2(k)) % Size)
        {
            if (states[h] == EXIST && keys[h] == k)
                return h;
        }
        return -1;
    }
    void insert(Key k, Value v)
    {
        int index = find(k);
        if (index != -1)
        {
            values[index] = v;
            return;
        }

        if (2 * keySize >= Size)
        {
            ++lgM;
            resize();
        }

        int h = hash1(k);
        while (states[h] == EXIST)
        {
            h = (h + hash2(k)) % Size;
        }

        keys[h] = k;
        values[h] = v;
        states[h] = EXIST;

        ++keySize;
    }

    // 删除
    void Delete(Key k)
    {
        int index = find(k);

        if (index == -1) return;

        states[index] = DELETED;
        --keySize;

        if (Size >= 31 && 8 * keySize <= Size)
        {
            --lgM;
            resize();
        }
    }

    void print()
    {
        for (int i = 0; i < Size; ++i)
        {
            if (states[i] == EXIST)
                std::cout << keys[i] << "-" << values[i] << " ";
        }
    }
private:

    void resize()
    {
        int oldSize = Size;
        Size = PRIMES[lgM];
        Key *tempkeys = new Key[Size];
        Value *tempvalues = new Value[Size];
        State *tempstates = new State[Size];
        for (int i = 0; i < Size; ++i)
            tempstates[i] = EMPTY;

        for (int i = 0; i < oldSize; ++i)
        {
            if (states[i] == EXIST)
            {
                int h = hash1(keys[i]);
                while (states[h] == EXIST)
                    h = (h + hash2(keys[i])) % Size;
                tempkeys[h] = keys[i];
                tempvalues[h] = values[i];
                states[h] = EXIST;
            }
        }
        delete[] keys;
        delete[] values;
        delete[] states;

        keys = tempkeys;
        values = tempvalues;
        states = tempstates;
    }
    int keySize;
    int Size;
    Key *keys;
    Value *values;
    State *states;
    int lgM;
    static int PRIMES[32];
};

template <typename Key, typename Value>
int  doubleHashingHashTable<Key, Value>::PRIMES[32] =
{
    1, 1, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381,
    32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301,
    8388593, 16777213, 33554393, 67108859, 134217689, 268435399,
    536870909, 1073741789, 2147483647
};


#endif // DOUBLEHASHINGHASHTABLE_H_
