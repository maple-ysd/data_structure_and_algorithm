#ifndef SPARSEVECTOR_H_
#define SPARSEVECTOR_H_


/** 基于红黑树与哈希表的map和unordered_map实现与Set、hashSet类似，
 *  这里就不再实现，直接使用c++标准库里的map与unordered_map
 */

#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <stdexcept>

// 键为int， 值为double
class sparseVector
{
public:
    sparseVector(int d = 2): dimension(d) {}
    sparseVector(std::map<int, double> m, int d): myMap(m), dimension(d) {};
    int size() { return myMap.size(); }
    bool empty() { return size() == 0; }
    double &get(int k)
    {
        if (myMap.find(k) == myMap.end())
            throw std::invalid_argument("this key does not exist.\n");
        return myMap[k];
    }
    void insert(int k, double v)
    {
        if (v == 0)
        {
            myMap.remove(k);
            return;
        }
        auto ret = myMap.insert(std::make_pair(k, v));
        if (ret.second == false)
            myMap[k] = v;
    }
    void remove(int k)
    {
        myMap.erase(k);
    }
    sparseVector operator+(sparseVector &rhs)
    {
        if (dimension != rhs.dimension)
            throw std::invalid_argument("two vectors are of different dimensions.\n");
        sparseVector ret(myMap, dimension);
        for (auto it = myMap.begin(); it != myMap.end(); ++it)
            ret.myMap[it->first] += rhs.myMap[it->first];
        return ret;
    }
    double operator*(sparseVector &rhs)
    {
        if (dimension != rhs.dimension)
            throw std::invalid_argument("two vectors are of different dimensions.\n");
        double sum = 0.0;
        if (myMap.size() <= rhs.myMap.size())
        {
            for (auto it = myMap.begin(); it != myMap.end(); ++it)
            sum += myMap[it->first] * rhs.myMap[it->first];
        }
        else
        {
            for (auto it = rhs.myMap.begin(); it != rhs.myMap.end(); ++it)
            sum += myMap[it->first] * rhs.myMap[it->first];
        }
        return sum;
    }
    double dot(const double *arr, int n)
    {
        if (n != dimension)
            throw std::invalid_argument("two vectors are of different dimensions.\n");
        double sum = 0.0;
        for (auto it = myMap.begin(); it != myMap.end(); ++it)
            sum += myMap[it->first] * arr[it->first];
        return sum;
    }
    void print()
    {
        for (auto it = myMap.begin(); it != myMap.end(); ++it)
            std::cout << it->first << "-" << it->second << " ";
    }
    void setDimension(int n)
    {
        dimension = n;
    }
    int getDimension()
    {
        return dimension;
    }
private:
    std::map<int, double> myMap;    // 或者 std::unordered_map<int, double> myMap;
    int dimension;
};

#endif // SPARSEVECTOR_H_
