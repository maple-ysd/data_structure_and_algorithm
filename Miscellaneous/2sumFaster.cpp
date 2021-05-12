#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

// 假设序列已经有序(从小到大)

int _2sumFaster(int arr[], int N)
{
    if (arr[0] > 0 || arr[N - 1] < 0)   // 排除全为负或全为正的情况
        return 0;

    int cnt = 0;    // 计数和为0的整数对
    for (int i = 0, j = N - 1; i < j; )
    {
        if (arr[i] + arr[j] > 0)
            --j;
        else if (arr[i] + arr[j] < 0)
            ++i;
        else
        {
            if (arr[i] == 0)
            {
                cnt += (j - i + 1) * (j - i) / 2;       // 处理中间部分连续为0或全部为0的情况
                break;
            }
            int cnt1 = 1;       // 记录连续相等的数个数
            int cnt2 = 1;
            while (arr[i] == arr[i + 1])
            {
                ++i;
                ++cnt1;
            }
            while (arr[j] == arr[j - 1])
            {
                --j;
                ++cnt2;
            }
            cnt += cnt1 * cnt2;
            ++i;
            ++j;
        }
    }
    return cnt;
}

int main()
{
    const int Min = -4;
    const int Max = 3;
    const int N = 100000;
    default_random_engine e;
    uniform_int_distribution<int> u(Min, Max);
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = u(e);
    sort(arr, arr + N);
//    for (auto i : arr)
//        cout << i << " ";
//    cout << endl;

    cout << _2sumFaster(arr, N) << endl;
    return 0;

}
