#include "BoyerMoore.h"
using namespace std;

BoyerMoore::BoyerMoore(string pat): pattern(pat), right(R)
{
    for (int i = 0; i < R; ++i)
        right[i] = -1;
    int sz = pattern.size();        // 不包含在模式串中
    for (int i = 0; i < sz; ++i)
        right[pattern[i]] = i;      // 出现在模式串中的最右位置
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
        if (skip == 0) return i;        // 找到匹配
    }
    return N;                           // 未找到匹配
}
