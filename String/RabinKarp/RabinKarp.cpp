#include "RabinKarp.h"

using namespace std;

RabinKarp::RabinKarp(string pat): pattern(pat), M(pattern.size()), Q(997)
{
    RM = 1;
    for (int i = 1; i <= M - 1; ++i)
        RM = (R * RM) % Q;      // ���ڼ�ȥ��һ������ʱ�ļ���
    patHash = hash(pattern, M);
}

int RabinKarp::search(string txt)
{
    // ���ı��в�����ȵ�ɢ��ֵ
    int N = txt.size();
    long txtHash = hash(txt, M);
    if (patHash == txtHash) return 0;   // һ��ʼ��ƥ��ɹ�

    for (int i = M; i < N; ++i)
    {
        // ��ȥ��һ�����֣��������һ�������ٴμ��ƥ��
        txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;
        txtHash = (txtHash * R + txt[i]) % Q;
        if (patHash == txtHash) return i - M + 1;
    }
    return N;
}

long RabinKarp::hash(string str, int M)
{
    long hs = 0;
    for (int i = 0; i < M; ++i)
    {
        hs = (R * hs + str[i]) % Q;
    }
    return hs;
}
