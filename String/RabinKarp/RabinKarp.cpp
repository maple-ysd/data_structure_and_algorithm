#include "RabinKarp.h"

using namespace std;

RabinKarp::RabinKarp(string pat): pattern(pat), M(pattern.size()), Q(997)
{
    RM = 1;
    for (int i = 1; i <= M - 1; ++i)
        RM = (R * RM) % Q;      // 用于减去第一个数字时的计算
    patHash = hash(pattern, M);
}

int RabinKarp::search(string txt)
{
    // 在文本中查找相等的散列值
    int N = txt.size();
    long txtHash = hash(txt, M);
    if (patHash == txtHash) return 0;   // 一开始就匹配成功

    for (int i = M; i < N; ++i)
    {
        // 减去第一个数字，加上最后一个数字再次检查匹配
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
