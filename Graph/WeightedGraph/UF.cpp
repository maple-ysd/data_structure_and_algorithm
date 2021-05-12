#include "UF.h"

UF::UF(int N)
{
    id = new int[N];
    sz = new int[N];
    cnt = N;
    for (int i = 0; i < N; ++i)
    {
        id[i] = i;
        sz[i] = 1;
    }
}

int UF::find(int v)
{
    while (id[v] != v)
        v = id[v];
    return v;
}

void UF::Union(int v, int w)
{
    if (connected(v, w)) return;

    int pv = find(v);
    int pw = find(w);
    if (sz[pv] < sz[pw])
    {
        id[pv] = pw;
        sz[pw] += sz[pv];
    }
    else
    {
        id[pw] = pv;
        sz[pv] += sz[pw];
    }
    --cnt;
}
