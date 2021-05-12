#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include "PrimarySort.h"
using namespace std;
// 测试单次排序时间
clock_t runTime(string str, double *arr, int n)
{
    char c;
    if (str == "selectSort") c = 's';
    else if (str == "insertSort") c = 'i';
    else if (str == "insertSortWithSentinel") c = 'b';
    else if (str == "insertSortWithSentinel2") c = 'B';
    clock_t start = clock();
    switch (c)
    {
        case 's': selectSort(arr, n);
        case 'i': insertSort(arr, n);
        case 'b': insertSortWithSentinel(arr, n);
        case 'B': insertSortWithSentinel2(arr, n);
    }
    clock_t duration = clock() - start;
    return duration;
//    return 1.0 * duration / CLOCKS_PER_SEC;        // in seconds
}
// 测试T次排序时间
double repeat(string str, double *arr, int n, int T)
{
    default_random_engine e(time(0));
    uniform_real_distribution<double> u(-100000, 100000);

    clock_t total = 0.0;
    for (int i = 0; i < T; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            arr[i] = u(e);
        };
//        // 测试逆序
//        for (int i = 0, j = n; i < n; ++i, --j)
//            arr[i] = j;
        total += runTime(str, arr, n);
    }
    return 1.0 * total / CLOCKS_PER_SEC;
}

int main()
{
    int n, t;
    cout << "please enter the size of array to be sorted, and how many times you want to repeat:\n";
    cin >> n >> t;
    double arr[n];
//    double t2 = repeat("insertSort", arr, n, t);
//    cout << "insert sort time: " << t2 << endl;
////    double t1 = repeat("selectSort", arr, n, t);
////    cout << "select sort time: " << t1 << endl;
//
//    // 测试哨兵
//    double t3 = repeat("insertSortWithSentinel", arr, n, t);
//    cout << "insert sort with sentinel: " << t3 << endl;
//
//
//    // 测试右移一位代替交换
//    double t4 = repeat("insertSortWithSentinel2", arr, n, t);
//    cout << "insert sort with sentinel2: " << t4 << endl;

    // 测试主键相等：用bernoulli_distribution产生0 或 1
    default_random_engine e(time(0));
    bernoulli_distribution bd(0.5);
    double tot5 = 0.0;
    double tot6 = 0.0;
    for (int i = 0; i < t; ++i)
    {
        for (int i = 0; i < n; ++i)
            arr[i] = bd(e);
        tot5 += runTime("selectSort", arr, n);
    }
    cout << "select sort time: " << tot5 / CLOCKS_PER_SEC << endl;

    for (int i = 0; i < t; ++i)
    {
        for (int i = 0; i < n; ++i)
            arr[i] = bd(e);
        tot6 += runTime("insertSort", arr, n);
    }
    cout << "insert sort time: " << tot6 / CLOCKS_PER_SEC << endl;

    return 0;
}
