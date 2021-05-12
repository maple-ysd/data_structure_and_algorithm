#ifndef KENDALLTAUDISTANCE_H_
#define KENDALLTAUDISTANCE_H_

/*****************************************
kendall tau distance
求两个排列的kendall tau 距离
也就是求一个序列基于另一个序列的逆序对数
为便于理解，先给出暴力解法，再给出归并解法
******************************************/
// 暴力解法 O（n^2）
int kendallTauDistance(int *arr1, int *arr2, int n)
{
    // 建立一个i -> arr1[i]的逆映射：arr[i] -> i
    int arr1Inversed[n];
    for (int i = 0; i < n; ++i)
        arr1Inversed[arr1[i]] = i;

    // 逆序对数
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            if (arr1Inversed[arr2[i]] > arr1Inversed[arr2[j]])
                ++cnt;
        }
    return cnt;
}

// 归并解法 O(nlogn)
// 从暴力解法知，我们比较的是两个arr1Inversed[arr2[i]], arr1Inversed[arr2[j]]的大小
// 也就是在基准序列里的前后顺序
// 故而不妨构造一个这样的数组，通过归并求解

int countInversions(int *arr, int n);
int countInversions(int *arr, int *aux, int lo, int hi);
int countCombination(int *arr, int *aux, int lo, int mid, int hi);

int kendallTauDistance2(int *arr1, int *arr2, int n)
{
    // 建立一个i -> arr1[i]的逆映射：arr[i] -> i
    int arr1Inversed[n];
    for (int i = 0; i < n; ++i)
        arr1Inversed[arr1[i]] = i;
    // 对arr2数组做相应转换
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
