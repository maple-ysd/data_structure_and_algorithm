#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include "shellSort.h"
using namespace std;

int main()
{
//    // test correctness
//    int ar[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
////    shellSort(ar, 10);
//    shellSort2(ar, 10);
//    for (auto x : ar)
//        cout << x << " ";
//    cout << endl;



//    const int N = 100000;
//    int arr[N];
//    for (int i = 0, j = N; i < N; ++i, --j)
//        arr[i] = j;
//    clock_t start = clock();        // 太快了，可能看不到时间
//    shellSort(arr, N);
//    cout << (clock() - start)<< endl;
//
//    int arr2[N];
//    for (int i = 0, j = N; i < N; ++i, --j)
//        arr2[i] = j;
//    start = clock();
//    shellSort2(arr2, N);
//    cout << (clock() - start) << endl;

    // 测试最坏的希尔排序: 包含1-100 的100个数的序列
    int test[100];
    for (int i = 0; i < 100; ++i)
        test[i] = i + 1;
    int temp[100];
    int worst[100];
    clock_t maxT = 0;
    for (int i = 0; i < 10000000; ++i)
    {
        random_shuffle(begin(test), end(test));
        for (int i = 0; i < 100; ++i)
            temp[i] = test[i];
        clock_t start = clock();
        shellSort(test, 100);
        clock_t duration = clock() - start;
        if (duration > maxT)
        {
            maxT = duration;
            for (int i = 0; i < 100; ++i)
                worst[i] = temp[i];
        }
    }
    cout << maxT << endl;
    for (auto x : worst)
        cout << x << " ";
    cout << endl;
    return 0;
}
