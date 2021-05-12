#ifndef LINEARPROBINGHASHTABLE_H_
#define LINEARPROBINGHASHTABLE_H_

#include <cmath>        // for double log2(double)
#include <functional>   // for std::hash<T>模板类

template <typename Key, typename Value>
class linearProbingHashTable
{
    enum State{ EXIST, EMPTY, DELETED };
public:
    linearProbingHashTable(int sz)
    {
        Size = sz;
        keySize = 0;
        keys = new Key[sz];
        values = new Value[sz];
        states = new State[sz];
        lgM = log2(Size);           // 对应一个质数数组的下标

        for (int i = 0; i < sz; ++i)
            states[i] = EMPTY;
    }
    ~linearProbingHashTable()
    {
        delete[] keys;
        delete[] values;
        delete[] states;
    }
    bool empty() { return keySize == 0; }
    int size() { return keySize; }
    double loadFactor() { return 1.0 * keySize / Size; }
    int hash(Key k)
    {
        int h = std::hash<Key>()(k);
        if (lgM < 26 && lgM >= 0)
            h = h % PRIMES[lgM + 5];
        return h % Size;
    }
    // 查找
    // 返回下标，若没找到，则返回-1
    int find(Key k)
    {
        for (int i = hash(k); states[i] != EMPTY; i = (i + 1) % Size)
        {
            if (states[i] == DELETED) continue;
            else
            {
                if (keys[i] == k) return i;
            }
        }
        return -1;
    }
    // 插入
    void insert(Key k, Value v)
    {
        if (loadFactor() >= 0.5)
        {
            ++lgM;
            resize(2 * Size);
        }

        int index = find(k);
        if (index != -1)
        {
            keys[index] = k;
            values[index] = v;
            return;
        }

        int i = hash(k);
        while (states[i] == EXIST)
            i = (i + 1) % Size;

        states[i] = EXIST;
        keys[i] = k;
        values[i] = v;

        ++keySize;
    }
    // 删除
    void Delete(Key k)
    {
        int index = find(k);
        if (index == -1) return;

        states[index] = DELETED;
        --keySize;

        if (Size > 31 && loadFactor() <= 1.0 / 8)
        {
            --lgM;
            resize(Size / 2);
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
    // resize
    void resize(int newSize)
    {
        int oldSize = Size;
        Size = newSize;
        Key* tempkeys = new Key[newSize];
        Value* tempvalues = new Value[newSize];
        State* tempstates = new State[newSize];
        for (int i = 0; i < newSize; ++i)
            tempstates[i] = EMPTY;

        for (int i = 0; i < oldSize; ++i)
        {
            if (states[i] == EXIST)
            {
                int h = hash(keys[i]);
                while (tempstates[h] == EXIST)
                {
                    h = (h + 1) % Size;
                }
                tempstates[h] = EXIST;
                tempkeys[i] = keys[i];
                tempvalues[i] = values[i];
            }
        }
        delete []states;
        delete []keys;
        delete []values;

        states = tempstates;
        values = tempvalues;
        keys = tempkeys;
    }

    int Size;
    int keySize;

    Value *values;
    Key *keys;
    State *states;

    int lgM;
    // 小于2的幂次的最大质数 < 2^i  i从0->31(前面的两项不符合)
    // 主要用于(与lgM一起)动态调整大小后，均匀的散列
    static const int PRIMES[32];
};

template <typename Key, typename Value>
const int linearProbingHashTable<Key, Value>::PRIMES[32] = {
        1, 1, 3, 7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191, 16381,
        32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301,
        8388593, 16777213, 33554393, 67108859, 134217689, 268435399,
        536870909, 1073741789, 2147483647
    };
#endif // LINEARPROBINGHASHTABLE_H_
