#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

// ���������Ѿ�����(��С����)

int _2sumFaster(int arr[], int N)
{
    if (arr[0] > 0 || arr[N - 1] < 0)   // �ų�ȫΪ����ȫΪ�������
        return 0;

    int cnt = 0;    // ������Ϊ0��������
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
                cnt += (j - i + 1) * (j - i) / 2;       // �����м䲿������Ϊ0��ȫ��Ϊ0�����
                break;
            }
            int cnt1 = 1;       // ��¼������ȵ�������
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
