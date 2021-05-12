#ifndef KENDALLTAUDISTANCE_H_
#define KENDALLTAUDISTANCE_H_

/*****************************************
kendall tau distance
���������е�kendall tau ����
Ҳ������һ�����л�����һ�����е��������
Ϊ������⣬�ȸ��������ⷨ���ٸ����鲢�ⷨ
******************************************/
// �����ⷨ O��n^2��
int kendallTauDistance(int *arr1, int *arr2, int n)
{
    // ����һ��i -> arr1[i]����ӳ�䣺arr[i] -> i
    int arr1Inversed[n];
    for (int i = 0; i < n; ++i)
        arr1Inversed[arr1[i]] = i;

    // �������
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            if (arr1Inversed[arr2[i]] > arr1Inversed[arr2[j]])
                ++cnt;
        }
    return cnt;
}

// �鲢�ⷨ O(nlogn)
// �ӱ����֪ⷨ�����ǱȽϵ�������arr1Inversed[arr2[i]], arr1Inversed[arr2[j]]�Ĵ�С
// Ҳ�����ڻ�׼�������ǰ��˳��
// �ʶ���������һ�����������飬ͨ���鲢���

int countInversions(int *arr, int n);
int countInversions(int *arr, int *aux, int lo, int hi);
int countCombination(int *arr, int *aux, int lo, int mid, int hi);

int kendallTauDistance2(int *arr1, int *arr2, int n)
{
    // ����һ��i -> arr1[i]����ӳ�䣺arr[i] -> i
    int arr1Inversed[n];
    for (int i = 0; i < n; ++i)
        arr1Inversed[arr1[i]] = i;
    // ��arr2��������Ӧת��
    int arr2Inversed[n];
    for (int i = 0; i < n; ++i)
        arr2Inversed[i] = arr1Inversed[arr2[i]];
    return countInversions(arr2Inversed, n);
}
int countInversions(int *arr, int n)
{
    int aux[n];
    return countInversions(arr, aux, 0, n - 1);
}

int countInversions(int *arr, int *aux, int lo, int hi)
{
    if (hi <= lo) return 0;

    int mid = lo + (hi - lo) / 2;
    int countLeft = countInversions(arr, aux, lo, mid);
    int countRight = countInversions(arr, aux, mid + 1, hi);
    return countLeft + countRight + countCombination(arr, aux, lo, mid, hi);
}

int countCombination(int *arr, int *aux, int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; ++i)
        aux[i] = arr[i];
    int cnt = 0;
    int left = lo;
    int right = mid + 1;
    int arrIndex = lo;
    while (left <= mid && right <= hi)
    {
        if (aux[left] > aux[right])
        {
            arr[arrIndex++] = aux[right++];
            cnt += mid - left + 1;
        }
        else
        {
            arr[arrIndex++] = aux[left++];
        }
    }
    while (left <= mid)
        arr[arrIndex++] = aux[left++];
    return cnt;
}
#endif // KENDALLTAUDISTANCE_H_
