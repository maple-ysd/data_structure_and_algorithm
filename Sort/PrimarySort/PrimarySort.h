#ifndef PRIMARYSORT_H_
#define PRIMARYSORT_H_

// 简单选择排序
// O(N^2)
// 交换N次，比较N(N-1)/2
// 比较次数固定，交换次数固定，与初始序列是否有序无关
void selectSort(double *arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int min = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[min]) min = j;
        std::swap(arr[i], arr[min]);
    }
}

// 插入排序（适合已基本有序的情况）
// O(N^2)
// 最好情况：初始数组已经有序，只需比较N-1次即可，无交换
// 最坏情况：逆序，需要比较约N^2 / 2次， 交换N^2 / 2次
// 平均情况：随机， 需要比较约N^2 / 4次， 交换N^2 / 4次
void insertSort(double *arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
            std::swap(arr[j], arr[j - 1]);
    }
}
// 带哨兵的插排
void insertSortWithSentinel(double *arr, int n)
{
    int minIndex = 0;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] < arr[minIndex])
            minIndex = i;
    }
    std::swap(arr[0], arr[minIndex]);
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; arr[j] < arr[j - 1]; --j)
            std::swap(arr[j], arr[j - 1]);
    }
}

// 通过右移一位代替交换
void insertSortWithSentinel2(double *arr, int n)
{
    int minIndex = 0;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] < arr[minIndex])
            minIndex = i;
    }
    std::swap(arr[0], arr[minIndex]);
    for (int i = 1; i < n; ++i)
    {
        int temp = arr[i];
        int j;
        for (j = i; temp < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}

#endif // PRIMARYSORT_H_
