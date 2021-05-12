#ifndef QUICKSORT_H_
#define QUICKSORT_H_

 /****************
 �������� ƽ��ʱ�临�Ӷ�~ 2NlnN ~1.39NlogN
 *****************/

#include <algorithm>
void quickSort(int *arr, int lo, int hi);

int subArraySize0 = 0;
int subArraySize1 = 0;
int subArraySize2 = 0;

void quickSort(int *arr, int n)
{
    // ���ϴ�ƣ����������������Ӱ��
    std::random_shuffle(arr, arr + n);
    quickSort(arr, 0, n - 1);
}

int partition(int *arr, int lo, int hi)
{
    int pivot = arr[lo];
    int loIndex = lo;
    int hiIndex = hi + 1;
    while (true)
    {
        while (arr[++loIndex] < pivot)
            if (loIndex == hi) break;
        while (pivot < arr[--hiIndex])
            if (hiIndex == lo) break;
        if (loIndex >= hiIndex)
            break;
        std::swap(arr[loIndex], arr[hiIndex]);
    }
    std::swap(arr[lo], arr[hiIndex]);
    return hiIndex;
}

void check(int sz)
{
    if (sz == 0)
        ++subArraySize0;
    else if (sz == 1)
        ++subArraySize1;
    else if (sz == 2)
        ++subArraySize2;
}
void quickSort(int *arr, int lo, int hi)
{

    if (hi <= lo) return;
    int part = partition(arr, lo, hi);

    int leftPart = part - lo;
    int rightPart = hi - part;

    check(leftPart);
    check(rightPart);

    quickSort(arr, lo, part - 1);
    quickSort(arr, part + 1, hi);
}

/******************************
�����з�, �ֳ����ݣ� �����ڴ������ظ�Ԫ�ص����飬 ȱ���ǽ��������϶ࣨ�����ڲ��ظ�������£�
*******************************/

void quickSort3Way(int *arr, int lo, int hi);

void quickSort3Way(int *arr, int n)
{
    std::random_shuffle(arr, arr + n);
    quickSort3Way(arr, 0, n - 1);
}

int compare(int x, int y)
{
    if (x < y) return -1;
    else if ( x > y) return 1;
    else return 0;
}

void quickSort3Way(int *arr, int lo, int hi)
{
    if (hi <= lo) return;
    int lower = lo;
    int i = lo + 1;
    int higher = hi;

    int pivot = arr[lo];
    while (i <= higher)
    {
        int cmp = compare(arr[i], pivot);
        if (cmp < 0)
        {
            std::swap(arr[lower++], arr[i++]);
        }
        else if (cmp > 0)
        {
            std::swap(arr[i], arr[higher--]);
        }
        else
        {
            ++i;
        }
    }
    // ����arr[lo, ..., lower - 1] < arr[lower, ... , higher] = pivot < arr[higher + 1, ... , hi]
    quickSort3Way(arr, lo, lower - 1);
    quickSort3Way(arr, higher + 1, hi);
}

/****************************
�����ŵĿ���,���������С��Сʱʹ�ò��Ÿ��죬������С�����Ƶ���ݹ飩
*****************************/
void quickSortWithInsertSort(int *arr, int lo, int hi);

void quickSortWithInsertSort(int *arr, int n)
{
    std::random_shuffle(arr, arr + n);
    quickSortWithInsertSort(arr, 0, n - 1);
}

void insertSort(int *arr, int lo, int hi)
{
    for (int i = lo + 1; i <= hi; ++i)
    {
        int temp = arr[i];
        int j;
        for (j = i; j > lo && temp < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}

void quickSortWithInsertSort(int *arr, int lo, int hi)
{
    if (hi <= lo) return;
    if (hi - lo + 1 < 10)
    {
        insertSort(arr, lo, hi);
        return;
    }
    int part = partition(arr, lo, hi);
    quickSortWithInsertSort(arr, lo, part - 1);
    quickSortWithInsertSort(arr, part + 1, hi);
}
#endif // QUICKSORT_H_


/*******************************************
���ٵ������з�
********************************************/

void quickSortFast3Way(int *arr, int lo, int hi);

void quickSortFast3Way(int *arr, int n)
{
    std::random_shuffle(arr, arr + n);
    quickSortFast3Way(arr, 0, n - 1);
}

/***********************************************************************************
arr[lo...p], arr[p + 1, .........,i,............,j,.........,q - 1],arr[q,...,hi]
    pivot               <pivot         ������         >pivot              pivot
************************************************************************************/
void quickSortFast3Way(int *arr, int lo, int hi)
{
    if (hi <= lo) return;

    int pivot = arr[lo];
    // ��������ָ�룬i���������ұ�����j�������������
    int i = lo;
    int j = hi + 1;
    // ��������ָ�룬p��arr[lo...p]������ֵa[lo]�� q��arr[q...hi]ͬ��������ֵa[lo]
    int p = lo;
    int q = hi + 1;

    while (true)
    {
        while (arr[++i] < pivot)
        {
            if (i == hi) break;
        }
        while (arr[--j] > pivot)
        {
            if (j == lo) break;
        }
        if (i == j && arr[i] == pivot)
            std::swap(arr[++p], arr[lo]);
        if (i >= j)
            break;
        std::swap(arr[i], arr[j]);
        if (arr[i] == pivot) std::swap(arr[++p], arr[i]);
        if (arr[j] == pivot) std::swap(arr[--q], arr[j]);
    }
    // ����arr[lo,...,p]��arr[q,...,hi]����pivot
    // arr[p + 1,...,i] < pivot;
    // arr[i + 1,...q - 1] > pivot;
    // ������pivot�Ĳ����Ƶ��м䣬�����Ϊ�� <pivot, pivot, >pivot
    i = j + 1;
    for (int k = lo; k <= p; ++k) std::swap(arr[k], arr[j--]);
    for (int k = hi; k >= q; --k) std::swap(arr[k], arr[i++]);
    // �任��arr[lo,...,j - 1] < pivot; arr[j,...,i] ==pivot�� arr[i + 1,...,hi] > pivot

    quickSortFast3Way(arr, lo, j);
    quickSortFast3Way(arr, i, hi);
}
