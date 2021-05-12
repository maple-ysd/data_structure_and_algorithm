#ifndef SEQLIST_H_
#define SEQLIST_H_

#include <iostream>
#include <stdexcept>
// dynamic sequence list
typedef int ElemType;
typedef struct
{
    ElemType *data;
    int length;
    int capacity;
}SeqList;

void InitSeqList(SeqList &L, int cap = 10)       // initialization
{
    L.data = new ElemType[cap];
    if (!L.data)
    {
        std::cerr << "memory allocation failure";
        std::exit(EXIT_FAILURE);
    }
    L.length = 0;
    L.capacity = cap;
}
void ClearSeqList(SeqList &L)
{
    L.length = 0;
}
void DestroySeqList(SeqList &L)
{
    if (L.data)
        delete[] L.data;
}
bool IsEmpty(const SeqList &L)
{
    return L.length == 0;
}
int GetLength(const SeqList &L)
{
    return L.length;
}
ElemType GetElem(const SeqList &L, int i)    // i : array index
{
    if (i < 0 || i > L.length - 1)
        throw std::out_of_range("index out of boundary");
    else
        return L.data[i];
}
int LocateElem(const SeqList &L, ElemType x)     // Get array index
{
    for (int i = 0; i < L.length; ++i)
    {
        if (L.data[i] == x)
            return i;   // if found, return array index
    }
    return -1;               // if not found, return -1
}

void ResizeSeqList(SeqList &L)
{
    ElemType *p = L.data;
    L.capacity = L.capacity ? L.capacity * 2 : 1;
    L.data = new ElemType(L.capacity);
    if (L.data == nullptr)
    {
        std::cout << "memory allocation failure.\n";
        std::exit(EXIT_FAILURE);
    }
    for (int i = 0; i < L.length; ++i)
        L.data[i] = p[i];
    delete p;
}

void InsertSeqList(SeqList &L, int i, ElemType x) // insert x in position i
{
    // valid insertion range is [0, length]
    if (i < 0 || i > L.length)
        throw std::out_of_range("invalid insertion position");
    if (L.length == L.capacity) ResizeSeqList(L);  // if you don't want to resize, just throw out_of_range("already full")
    for (int j = L.length; j > i; j--)
        // elements in range[length-1 ... i] move back one step
        L.data[j] = L.data[j - 1];
    L.data[i] = x;
    L.length += 1;
}

void DelSeqList(SeqList &L, int i)
{
    if (i < 0 || i > L.length - 1)
        throw std::out_of_range("invalid delete position");
    if (IsEmpty(L)) throw std::out_of_range("already empty");
    for (int j = i; j < L.length - 1; ++j)
        L.data[j] = L.data[j + 1];
    L.length -= 1;
}

void DisplaySeqList(const SeqList &L)
{
    for (int i = 0; i < L.length; ++i)
        std::cout << L.data[i] << " ";
    std::cout << std::endl;
}

#endif // SEQLIST_H_
