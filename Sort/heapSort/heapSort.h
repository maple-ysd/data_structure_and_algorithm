#ifndef HEAPSORT_H_
#define HEAPSORT_H_

/*********************************************
堆排序：
先下沉构造一个大顶堆
然后再下沉销毁大顶堆，同时生成一个有序非递减数列
**********************************************/
// 数组从1开始
void sink(int *arr, int k, int n);
void heapSort(int *arr, int n)
{
    for (int i = n / 2; i >= 1; --i)
    {
        sink(arr, i, n);
    }
    while (n > 1)
    {
        std::swap(arr[1], arr[n--]);
        sink(arr, 1, n);
    }
}

void sink(int *arr, int k, int n)
{
    while (2 * k <= n)
    {
        int j = 2 * k;
        if (j < n && arr[j] < arr[j + 1]) ++j;
        if (arr[k] >= arr[j]) break;
        std::swap(arr[k], arr[j]);
        k = j;
    }
}

/************************************
考虑数组从0开始
*************************************/
void heapSort2(int *arr, int n)
{
    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        int k = i;
        while (2 * k + 1 < n)
        {
            int j = 2 * k + 1;
            if (j + 1 < n && arr[j] < arr[j + 1]) ++j;
            if (arr[k] >= arr[j])
                break;
            std::swap(arr[k], arr[j]);
            k = j;
        }
    }
    while (n > 0)
    {
        std::swap(arr[0], arr[n - 1]);
        --n;
        int k = 0;
        while (2 * k + 1 < n)
        {
            int j = 2 * k + 1;
            if (j + 1 < n && arr[j] < arr[j + 1]) ++j;
            if (arr[k] >= arr[j])
                break;
            std::swap(arr[k], arr[j]);
            k = j;
        }
    }
}

#endif // HEAPSORT_H_
