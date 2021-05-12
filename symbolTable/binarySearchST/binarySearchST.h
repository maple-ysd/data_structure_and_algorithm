#ifndef BINARYSEARCHST_H_
#define BINARYSEARCHST_H_

/**************************************************
有序数组（二分查找）实现符号表
***************************************************/

#include <string>
#include <stdexcept>
#include <algorithm>
typedef std::string Key;
typedef int Value;

const Key null = std::string("");

struct Iterator
{
    std::pair<Key*, Value*> kv;
    Iterator(Key *k, Value *v) { kv = std::make_pair(k, v);}
    void operator++() { ++kv.first; ++kv.second; }
    std::pair<Key, Value> operator*() { return std::make_pair(*kv.first, *kv.second); }
    bool operator!=(Iterator that) { return kv != that.kv; }
};

class binarySearchST
{
public:
    binarySearchST(): keys(new Key[2]), values(new Value[2]) {}
    ~binarySearchST() { delete[] keys; delete[] values; }
    bool isEmpty() { return Size == 0; }
    int size() { return Size; }
    Value get(Key k);
    int rank(Key k);
    Key select(int n);
    void put(Key k, Value v);
    void Delete(Key k);
    Key Min();
    Key Max();
    Key ceiling(Key k);
    Key floor(Key k);
    Iterator begin() { return Iterator(keys, values); }
    Iterator end() { return Iterator(keys + Size, values + Size); }
private:
    void resize(int newCapacity);
    Key *keys;
    Value *values;
    int Size = 0;
    int capacity = 2;
};

Value binarySearchST::get(Key k)
{
    if (k == null)
        throw std::invalid_argument("key can not be null.\n");
    if (isEmpty())
        throw std::runtime_error("binarySearchST is empty, get operation failed.\n");
    int r = rank(k);
    if (r < Size && keys[r] == k) return values[r];
    else
        throw std::invalid_argument("key does not exist.\n");
}

int binarySearchST::rank(Key k)
{
    if (k == null)
        throw std::invalid_argument("key can not be null.\n");
    int lo = 0;
    int hi = Size - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (k < keys[mid])
            hi = mid;
        else if (k > keys[mid])
            lo = mid + 1;
        else
            return mid;
    }
    return lo;      // lo 前面的键值都小于k
}
// rank 的递归实现
//int rank(Key k, int lo, int hi);
//int binarySearchST::rank(Key k)
//{
//    int lo = 0;
//    int hi = Size - 1;
//    return rank(k, lo, hi);
//}
//int rank(Key k, int lo, int hi)
//{
//    if (hi < lo) return lo;
//    int mid = lo + (hi - lo) / 2;
//    if (k < keys[mid])
//        return rank(k, lo, mid);
//    else if (k > keys[mid])
//        return rank(k, mid + 1, hi);
//    else
//        return mid;
//}

Key binarySearchST::select(int n)
{
    if (isEmpty() || n >= Size)
        throw std::invalid_argument("index is higher than size.\n");
    return keys[n];
}

void binarySearchST::put(Key k, Value v)
{
    if (k == null)
        throw std::invalid_argument("key can not be null.\n");
    int r = rank(k);
    if (r < Size && keys[r] == k)
    {
        values[r] = v;
        return;
    }
    if (Size == capacity)
        resize(capacity * 2);
    for (int i = Size; i > r; --i)
    {
        keys[i] = keys[i - 1];
        values[i] = values[i - 1];
    }
    keys[r] = k;
    values[r] = v;
    ++Size;
}
void binarySearchST::Delete(Key k)
{
    if (k == null)
        throw std::invalid_argument("key can not be null.\n");
    if (isEmpty())
        throw std::runtime_error("binarySearchST is empty, Delete operation failed.\n");
    int r = rank(k);

    if (r < Size && keys[r] == k)
    {
        for (int i = r + 1; i < Size; ++i)
        {
            keys[i - 1] = keys[i];
            values[i - 1] = values[i];
        }
        --Size;
    }
    else
        throw std::invalid_argument("key does not exist.\n");
    if (Size > 1 && Size == capacity / 4)
        resize(capacity / 2);
}

Key binarySearchST::Min()
{
    if (isEmpty())
        throw std::runtime_error("binarySearchST is empty, Min operation failed.\n");
    return keys[0];
}
Key binarySearchST::Max()
{
    if (isEmpty())
        throw std::runtime_error("binarySearchST is empty, Max operation failed.\n");
    return keys[Size - 1];
}
Key binarySearchST::ceiling(Key k)
{
    if (isEmpty())
        throw std::runtime_error("binarySearchST is empty, Max operation failed.\n");
    if (k == null)
        throw std::invalid_argument("key can not be null");
    int r = rank(k);
    if (r == Size)
        return null;
    return keys[r];
}
Key binarySearchST::floor(Key k)
{
    if (isEmpty())
        throw std::runtime_error("binarySearchST is empty, Max operation failed.\n");
    if (k == null)
        throw std::invalid_argument("key can not be null");
    int r = rank(k);
    if (r == 0)
        return null;
    if (keys[r] == k) return k;
    return keys[r - 1];
}
void binarySearchST::resize(int newCapacity)
{
    Key *tempKeys = new Key[newCapacity];
    Value *tempValues = new Value[newCapacity];
    std::copy(keys, keys + Size, tempKeys);
    std::copy(values, values + Size, tempValues);
    delete[] keys;
    delete[] values;
    keys = tempKeys;
    values = tempValues;
    capacity = newCapacity;
}

#endif // BINARYSEARCHST_H_
