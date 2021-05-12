#include "KMP.h"
using namespace std;

KMP::KMP(string pat): pattern(pat), dfa(R, vector<int>(pattern.size()))
{
    // ����dfa, dfa[text[i]][j]��ʾ�ı��ַ�text[i]��ģʽ��[j]ƥ��֮������һ���ı��ַ�s[i + 1]ƥ���ģʽ���е��ַ�λ��
    // ��ʼ��
    for (int i = 0; i < R; ++i)
        dfa[i][0] = 0;
    dfa[pattern[0]][0] = 1;


    int j, X;
    // X��ʾ������p[1...j-1]������״̬,��ʧ�ܺ����õ�״̬(��Ӧdfa��ĳһ��)
    // X = dfa[pattern[j]][X] ��������pattern[j]�󣬸���X��
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
