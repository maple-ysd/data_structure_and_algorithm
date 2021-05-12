#ifndef PRIMARYSORT_H_
#define PRIMARYSORT_H_

// ��ѡ������
// O(N^2)
// ����N�Σ��Ƚ�N(N-1)/2
// �Ƚϴ����̶������������̶������ʼ�����Ƿ������޹�
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

// ���������ʺ��ѻ�������������
// O(N^2)
// ����������ʼ�����Ѿ�����ֻ��Ƚ�N-1�μ��ɣ��޽���
// ������������Ҫ�Ƚ�ԼN^2 / 2�Σ� ����N^2 / 2��
// ƽ������������ ��Ҫ�Ƚ�ԼN^2 / 4�Σ� ����N^2 / 4��
void insertSort(double *arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
            std::swap(arr[j], arr[j - 1]);
    }
}
// ���ڱ��Ĳ���
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

// ͨ������һλ���潻��
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
