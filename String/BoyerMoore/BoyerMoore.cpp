#include "BoyerMoore.h"
using namespace std;

BoyerMoore::BoyerMoore(string pat): pattern(pat), right(R)
{
    for (int i = 0; i < R; ++i)
        right[i] = -1;
    int sz = pattern.size();        // ��������ģʽ����
    for (int i = 0; i < sz; ++i)
        right[pattern[i]] = i;      // ������ģʽ���е�����λ��
}
int BoyerMoore::search(string txt)
{
    int N = txt.size();
    int M = pattern.size();
    int i, j;
    int skip;
    for (i = 0; i <= N - M; i += skip)
    {
        skip = 0;
        for (j = M - 1; j >=0; --j)
        {
            if (txt[i + j] != pattern[j])
            {
                skip = j - right[txt[i + j]];
                if (skip < 1) skip = 1;
                break;
            }
        }
        if (skip == 0) return i;        // �ҵ�ƥ��
    }
    return N;                           // δ�ҵ�ƥ��
}
