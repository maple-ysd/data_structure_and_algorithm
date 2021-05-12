#ifndef NSUM_H_
#define NSUM_H_
/******************************************
求解数组中任意两数之和，三数之和，四数之和为一定值的组合个数
通用思路：三数之和转化为求sum - elem 的两数之和， 四数之和转
化为求3数之和...以此类推
两数之和可采用：先排序然后两端向中间逼近的方法
也可采用unordered_map来实现
*******************************************/
// _2sum, _3sum, _4sum ... _nsum problemss
// 求和为n的数对
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

// _2sum problem

// 先排序(<)，O（nlogn）, 从两边往中间走
int _2sum1(int arr[], int n, int sum)
{
    std::vector<int> vec;
    for (int i = 0; i < n; ++i)
        vec.push_back(arr[i]);
    std::sort(vec.begin(), vec.end());
    int cnt = 0;
    for (int i = 0, j = n - 1; i < j;)
    {
        if (vec[i] + vec[j] > sum)
            --j;
        else if (vec[i] + vec[j] < sum)
            ++i;
        else
        {
            if (vec[i] == vec[j])
            {
                cnt += (j - i + 1) * (j - i) / 2;
                break;
            }
            int cnt1 = 1;
            int cnt2 = 1;
            // 处理左边连续部分
            while (vec[i] == vec[i + 1])
            {
                ++i;
                ++cnt1;
            }
            // 处理右边连续部分
            while (vec[j] == vec[j - 1])
            {
                --j;
                ++cnt2;
            }
            cnt += cnt1 * cnt2;
            ++i;
            --j;
        }
    }
    return cnt;
}


// O（n）用unordered_map实现
int _2sum2(int arr[], int n, int sum)
{
    std::unordered_map<int, int> Map;
    for (int i = 0; i < n; ++i)
        ++Map[arr[i]];           // 第二个int值会被值初始化为0
    int cnt = 0;
    for (auto it = Map.begin(); it != Map.end(); ++it)
    {
        if (it->first * 2  == sum)
            cnt += it->second * (it->second -1);
        else if (Map.find(sum - it->first) != Map.end())
            cnt += it->second * Map[sum - it->first];
    }
    cnt /= 2;               // 因为前面重复计数1次
    return cnt;
}

// 3sum实现问题
// 1）用以上的两种_2sum方法实现。

// 这里为O（n^2logn）， 提前排序而不是在_2sum里面排序的话，复杂度可降为O（n^2）
int _3sum1(int arr[], int n, int sum)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        cnt += _2sum1(&arr[i + 1], n - (i + 1), sum - arr[i]);
    }
    return cnt;
}
// O(n^2)
int _3sum2(int arr[], int n, int sum)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        cnt += _2sum2(&arr[i + 1], n - (i + 1), sum - arr[i]);
    }
    return cnt;
}

// 2）预先保存两数之和,同时保存对应下标，判重
// O（n^2)
int _3sum3(int arr[], int n, int sum)
{
    std::unordered_map<int, std::vector<std::pair<int, int>>> Map;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            Map[arr[i] + arr[j]].push_back(std::make_pair(i, j));
        }
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (Map.find(sum - arr[i]) != Map.end())
        {
            for (auto x : Map[sum - arr[i]])
            {
                if (x.first != i && x.second != i)
                    ++cnt;
            }
        }
    }
    return cnt / 3;     // 因为对同一个三元组有3中可能的组合
}

// _4sum实现问题
// 基于_3sum实现
// O（n^3）
int _4sum1(int arr[], int n, int sum)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        cnt += _3sum2(&arr[i + 1], n - (i + 1), sum - arr[i]);
    }
    return cnt;
}
// 先求任意两数和，然后对所有可能的和遍历
// 若无需判重， 复杂度O（n^2）
// 最坏情况， 复杂度O（n^4）
int _4sum2(int arr[], int n, int sum)
{
    std::unordered_map<int, std::vector<std::pair<int, int>>> Map;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            Map[arr[i] + arr[j]].push_back(std::make_pair(i, j));
        }
    int cnt = 0;
    for (auto it = Map.begin(); it != Map.end(); ++it)
    {
        if (Map.find(sum - it->first) != Map.end())
        {
            for (auto x : Map[it->first])
                for (auto y : Map[sum - it->first])
                {
                    if (x.second < y.first) // 不重复的选择其中一种排列
                        ++cnt;
                }
        }
    }
    return cnt;
}

#endif // NSUM_H_
