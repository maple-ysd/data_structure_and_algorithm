#include "KMP.h"
using namespace std;

KMP::KMP(string pat): pattern(pat), dfa(R, vector<int>(pattern.size()))
{
    // 构造dfa, dfa[text[i]][j]表示文本字符text[i]与模式串[j]匹配之后，与下一个文本字符s[i + 1]匹配的模式串中的字符位置
    // 初始化
    for (int i = 0; i < R; ++i)
        dfa[i][0] = 0;
    dfa[pattern[0]][0] = 1;


    int j, X;
    // X表示当输入p[1...j-1]后进入的状态,即失败后重置的状态(对应dfa的某一列)
    // X = dfa[pattern[j]][X] （当输入pattern[j]后，更新X）
    for (X = 0, j = 1; j < pattern.size(); ++j)
    {
        for (int i = 0; i < R; ++i)
            dfa[i][j] = dfa[i][X];
        dfa[pattern[j]][j] = j + 1;
        X = dfa[pattern[j]][X];
    }
}

int KMP::search(string txt)
{
    int i, j;
    int M = pattern.size();
    int N = txt.size();
    for (i = 0, j = 0; i < N && j< M; ++i)
        j = dfa[txt[i]][j];

    if (j == M) return i - M;
    else return N;
}
