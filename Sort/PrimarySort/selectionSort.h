#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

// ��ѡ������
// O(N^2)
// ����N�Σ��Ƚ�N(N-1)/2
// �Ƚϴ����̶������������̶������ʼ�����Ƿ������޹�
void selectSort(int arr, int n)
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
void insertSort(int arr, int n)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
            std::swap(arr[j], arr[j - 1]);
    }
}

#endif // SELECTIONSORT_H_
