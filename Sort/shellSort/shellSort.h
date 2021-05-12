#ifndef SHELLSORT_H_
#define SHELLSORT_H_
#include <vector>
/******************
希尔排序
性能取决于所选的h序列与初始数组
*******************/

// 实时更新h值
void shellSort(int *arr, int n)
{
    if (n <= 0) return;
    int h = 1;
    while (h < n / 3)
        h = 3 * h + 1;
    while (h >= 1)
    {
        for (int i = h; i < n; ++i)
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h)
                std::swap(arr[j], arr[j - h]);
        h = h / 3;
    }
}

// 保存h值数组
void shellSort2(int *arr, int n)
{
    if (n <= 0) return;

    int h = 1;
    int number = 1;
    while (h < n / 3)
    {
        h = 3 * h + 1;
        ++number;
    }

    int increm[number];
    h = 1;
    for (int i = 0; i < number; ++i, h = 3 * h + 1)
    {
        increm[i] = h;
    }

    for (int k = number - 1; k >= 0; --k)
    {
        h = increm[k];
        for (int i = h; i < n; ++i)
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h)
                std::swap(arr[j], arr[j - h]);
    }
}
#endif // SHELLSORT_H_
