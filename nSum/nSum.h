#ifndef NSUM_H_
#define NSUM_H_
/******************************************
�����������������֮�ͣ�����֮�ͣ�����֮��Ϊһ��ֵ����ϸ���
ͨ��˼·������֮��ת��Ϊ��sum - elem ������֮�ͣ� ����֮��ת
��Ϊ��3��֮��...�Դ�����
����֮�Ϳɲ��ã�������Ȼ���������м�ƽ��ķ���
Ҳ�ɲ���unordered_map��ʵ��
*******************************************/
// _2sum, _3sum, _4sum ... _nsum problemss
// ���Ϊn������
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

// _2sum problem

// ������(<)��O��nlogn��, ���������м���
int _2sum1(int arr[], int n, int sum)
{
    std::vector<int> vec;
    for (int i = 0; i < n; ++i)
        vec.push_back(arr[i]);
    std::sort(vec.begin(), vec.end());
    int cnt = 0;
    for (int i = 0, j = n - 1; i < j;)
    {
        if (vec[i] + vec[j] > sum)
            --j;
        else if (vec[i] + vec[j] < sum)
            ++i;
        else
        {
            if (vec[i] == vec[j])
            {
                cnt += (j - i + 1) * (j - i) / 2;
                break;
            }
            int cnt1 = 1;
            int cnt2 = 1;
            // ���������������
            while (vec[i] == vec[i + 1])
            {
                ++i;
                ++cnt1;
            }
            // �����ұ���������
            while (vec[j] == vec[j - 1])
            {
                --j;
                ++cnt2;
            }
            cnt += cnt1 * cnt2;
            ++i;
            --j;
        }
    }
    return cnt;
}


// O��n����unordered_mapʵ��
int _2sum2(int arr[], int n, int sum)
{
    std::unordered_map<int, int> Map;
    for (int i = 0; i < n; ++i)
        ++Map[arr[i]];           // �ڶ���intֵ�ᱻֵ��ʼ��Ϊ0
    int cnt = 0;
    for (auto it = Map.begin(); it != Map.end(); ++it)
    {
        if (it->first * 2  == sum)
            cnt += it->second * (it->second -1);
        else if (Map.find(sum - it->first) != Map.end())
            cnt += it->second * Map[sum - it->first];
    }
    cnt /= 2;               // ��Ϊǰ���ظ�����1��
    return cnt;
}

// 3sumʵ������
// 1�������ϵ�����_2sum����ʵ�֡�

// ����ΪO��n^2logn���� ��ǰ�����������_2sum��������Ļ������Ӷȿɽ�ΪO��n^2��
int _3sum1(int arr[], int n, int sum)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        cnt += _2sum1(&arr[i + 1], n - (i + 1), sum - arr[i]);
    }
    return cnt;
}
// O(n^2)
int _3sum2(int arr[], int n, int sum)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        cnt += _2sum2(&arr[i + 1], n - (i + 1), sum - arr[i]);
    }
    return cnt;
}

// 2��Ԥ�ȱ�������֮��,ͬʱ�����Ӧ�±꣬����
// O��n^2)
int _3sum3(int arr[], int n, int sum)
{
    std::unordered_map<int, std::vector<std::pair<int, int>>> Map;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            Map[arr[i] + arr[j]].push_back(std::make_pair(i, j));
        }
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (Map.find(sum - arr[i]) != Map.end())
        {
            for (auto x : Map[sum - arr[i]])
            {
                if (x.first != i && x.second != i)
                    ++cnt;
            }
        }
    }
    return cnt / 3;     // ��Ϊ��ͬһ����Ԫ����3�п��ܵ����
}

// _4sumʵ������
// ����_3sumʵ��
// O��n^3��
int _4sum1(int arr[], int n, int sum)
{
    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        cnt += _3sum2(&arr[i + 1], n - (i + 1), sum - arr[i]);
    }
    return cnt;
}
// �������������ͣ�Ȼ������п��ܵĺͱ���
// ���������أ� ���Ӷ�O��n^2��
// ������ ���Ӷ�O��n^4��
int _4sum2(int arr[], int n, int sum)
{
    std::unordered_map<int, std::vector<std::pair<int, int>>> Map;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            Map[arr[i] + arr[j]].push_back(std::make_pair(i, j));
        }
    int cnt = 0;
    for (auto it = Map.begin(); it != Map.end(); ++it)
    {
        if (Map.find(sum - it->first) != Map.end())
        {
            for (auto x : Map[it->first])
                for (auto y : Map[sum - it->first])
                {
                    if (x.second < y.first) // ���ظ���ѡ������һ������
                        ++cnt;
                }
        }
    }
    return cnt;
}

#endif // NSUM_H_
