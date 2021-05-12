#ifndef HEAPSORT_H_
#define HEAPSORT_H_

/*********************************************
������
���³�����һ���󶥶�
Ȼ�����³����ٴ󶥶ѣ�ͬʱ����һ������ǵݼ�����
**********************************************/
// �����1��ʼ
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
���������0��ʼ
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
