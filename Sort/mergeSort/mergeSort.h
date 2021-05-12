#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <algorithm>
//void Sort(int *arr, int *aux, int lo, int hi);
//void Merge(int *arr, int *aux, int lo, int mid, int hi);

/*********************
�Զ����¹鲢
O(nlogn):    1/2 nlogn -> nlogn
**********************/

//void mergeSort(int *arr, int n)
//{
//    int aux[n];
//    Sort(arr, aux, 0, n - 1);
//}

//void Sort(int *arr, int *aux, int lo, int hi)
//{
//    if (hi <= lo) return;
//    int mid = lo + (hi - lo) / 2;
//
//    Sort(arr, aux, lo, mid);
//    Sort(arr, aux, mid + 1, hi);
//    Merge(arr, aux, lo, mid, hi);
//}

/*********************
�Ե����Ϲ鲢
O(nlogn):    1/2 nlogn -> nlogn
**********************/

//void mergeSort2(int *arr, int n)
//{
//    int aux[n];
//    for (int k = 1; k < n; k += k)
//    {
//        for (int i = 0; i < n - k; i += k + k)
//        {
//            int hi = std::min(n - 1, i + k + k - 1);
//            Merge(arr, aux, i, i + k - 1, hi);
//        }
//    }
//}

/*********************
��ͬ��Mergeʵ��
 *********************/

//void Merge(int *arr, int *aux, int lo, int mid, int hi)
//{
//    for (int i = lo; i <= hi; ++i)
//        aux[i] = arr[i];
//
//    int left = lo;
//    int right = mid + 1;
//    for (int k = lo; k <= hi; ++k)
//    {
//        if (left > mid)
//            arr[k] = aux[right++];
//        else if (right > hi)
//            arr[k] = aux[left++];
//        else if (aux[left] <= aux[right])
//            arr[k] = aux[left++];
//        else
//            arr[k] = aux[right++];
//    }
//}

//void Merge(int *arr, int *aux, int lo, int mid, int hi)
//{
//    for (int i = lo; i <= hi; ++i)
//        aux[i] = arr[i];
//    int left = lo;
//    int right = mid + 1;
//    int k = lo;
//    while (left <= mid && right <= hi)
//    {
//        if (aux[left] <= aux[right])
//           arr[k++] = aux[left++];
//        else
//            arr[k++] = aux[right++];
//    }
//    while (left <= mid)
//        arr[k++] = aux[left++];
//    while(right <= hi)
//        arr[k++] = aux[right++];
//}

// ���ٹ鲢��ͨ������벿�ֽ��򿽱������������ �Ӷ���ȥ�˱߽�Ƚ�
void Merge(int *arr, int *aux, int lo, int mid, int hi)
{
    int auxIndex;
    for (auxIndex = lo; auxIndex <= mid; ++auxIndex)
        aux[auxIndex] = arr[auxIndex];
    for (int i = hi; i > mid; --i)
        aux[auxIndex++] = arr[i];

    int left = lo;
    int right = hi;
    int k = lo;

    while (left <= right)
    {
        if (aux[left] <= aux[right])
            arr[k++] = aux[left++];
        else
            arr[k++] = aux[right--];
    }
}

/*************************************************************************
�鲢��������Ľ���(�ݹ�ʵ��)
1����������ݹ�Ľ�С���������
2����������Ƿ��Ѿ�����
3���ڵݹ��н����������������鸴�ƣ������̫���ˣ��Ͳ����ˣ����ǿ�����������Ե����Ϲ鲢��ʵ��
 *************************************************************************/
//
void Sort3(int *arr, int *aux, int lo, int hi);
void insertSort(int *arr, int lo, int hi);

void mergeSort3(int *arr, int n)
{
    int aux[n];
    Sort3(arr, aux, 0, n - 1);
}

void Sort3(int *arr, int *aux, int lo, int hi)
{
    if (hi <= lo) return;
    // ���赱��������������С�ڵ���15ʱ��ʹ�ò������򷨣����ǵݹ���ù鲢����
    if (hi - lo + 1 <= 15)
    {
        insertSort(arr, lo, hi);
        return;
    }
    int mid = lo + (hi - lo) / 2;
    Sort3(arr, aux, lo, mid);
    Sort3(arr, aux, mid + 1, hi);
    // ��������Ѿ����򣬲����κδ���
    if (arr[mid] > arr[mid + 1])
    {
        Merge(arr, aux, lo, mid, hi);
    }
}
// ��������ʵ�֣������СС�ڵ���15
void insertSort(int *arr, int lo, int hi)
{
    if (hi <= lo) return;
    // ��ǰ�����һ���ڱ�
    int minIndex = lo;
    for (int i = lo; i <= hi; ++i)
    {
        if (arr[i] < arr[minIndex])
            minIndex = i;
    }
    std::swap(arr[lo], arr[minIndex]);

    for (int i = lo + 1; i <= hi; ++i)
    {
        int temp = arr[i];
        int j;
        for (j = i; temp < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}

/******************************************************************
�Ե����ϣ� ����ʵ�֣�(��������ĸ���)
*******************************************************************/
void mergeSort4(int *arr, int n)
{
    int *a = arr;
    int *aux = new int[n];

    for (int seg = 1; seg < n; seg += seg)
    {
        for (int i = 0; i < n; i += seg + seg)
        {
            int left = i;
            int mid = n - 1 < i + seg - 1 ? n - 1 : i + seg - 1;
            int right = mid + 1;

            int hi = n - 1 < i + seg + seg - 1 ? n - 1 : i + seg + seg -1;
            int k = i;
            while (left <= mid && right <= hi)
            {
                if (a[left] <= a[right])
                    aux[k++] = a[left++];
                else
                    aux[k++] = a[right++];
            }
            while (left <= mid)
                aux[k++] = a[left++];
            while (right <= hi)
                aux[k++] = a[right++];
        }
        int *temp = a;
        a = aux;
        aux = temp;
    }
    if (a != arr)
    {
        for (int i = 0; i < n; ++i)
            arr[i] = a[i];
        delete[] a;
    }
    else
        delete[] aux;
}

#endif // MERGESORT_H_
