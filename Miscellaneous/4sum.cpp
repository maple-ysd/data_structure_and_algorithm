#include <iostream>
#include <map>
#include <list>
#include <random>
#include <ctime>
using namespace std;

// 暴力法 Brute force O(n^4)
// 对是否有序无限制
int _4sum1 (int arr[], int N)
{
    int cnt = 0;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            for (int k = j + 1; k < N; ++k)
                for (int m = k + 1; m < N; ++m)
                {
                    if (arr[i] + arr[j] + arr[k] + arr[m] == 0)
                        ++cnt;
                }
    return cnt;
}

// 查找对应键值的最小（true）与最大索引（false）
int binarySearch(int arr[], int elem, int low, int high, bool searchLow)
{
    if (low > high)
        return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] < elem)
        return binarySearch(arr, elem, mid + 1, high, searchLow);
    else if (arr[mid] > elem)
        return binarySearch(arr, elem, low, mid - 1, searchLow);
    else
    {
        int index;
        if (searchLow)
            index = binarySearch(arr, elem, low, mid - 1, true);
        else
            index = binarySearch(arr, elem, mid + 1, high, false);

        if (index != -1)
            return index;
        else
            return mid;
    }
}

//
// 要求有序（可以使用归并O（nlogn）提前排序， 这里假设已经有序)
int _4sum2(int arr[], int N)
{
    int cnt = 0;

    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            for (int k = j + 1; k < N; ++k)
            {
                int lowIndex = binarySearch(arr, arr[i] + arr[j] + arr[k], k + 1, N - 1, true);
                if (lowIndex == -1)
                    continue;
                int highIndex = binarySearch(arr, arr[i] + arr[j] + arr[k], k + 1, N - 1, false);
                cnt += highIndex - lowIndex + 1;
            }
    return cnt;
}

// 复杂度分析, 最好情况比以上两个都好n^3, 最差情况比以上两个都差,n^4logn
// 同样要求有序
int _4sum3(int arr[], int N)
{
    map<int, list<pair<int, int>>> m;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
        {
            int sum = arr[i] + arr[j];
            m[sum].push_back(make_pair(i, j));
        }
    int cnt = 0;
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        auto pos = m.find(-(it->first));
        if (pos != m.end())
        {
            for (auto iter1 = (it->second).begin(); iter1 != (it->second).end(); ++iter1)
            for (auto iter2 = pos->second.begin(); iter2 != pos->second.end(); ++iter2)
            {
                if (iter1->second < iter2->first)
                    ++cnt;
            }
        }
    }
    return cnt;
}


int main()
{
    const int N = 1000;
    default_random_engine e;
    uniform_int_distribution<int> u(-20, 20);
    int arr[N];
    for (int i = 0; i < N; ++i)
    {
        arr[i] = u(e);
    }
    int ret;
    clock_t duration = clock();
    ret = _4sum1(arr, N);
    duration = clock() - duration;
    cout << duration / CLOCKS_PER_SEC << endl;

    duration = clock();
    ret = _4sum2(arr, N);
    duration = clock() - duration;
    cout << duration / CLOCKS_PER_SEC << endl;

    duration = clock();
    ret = _4sum3(arr, N);
    duration = clock() - duration;
    cout << duration / CLOCKS_PER_SEC << endl;

    return 0;

}
