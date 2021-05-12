#include <iostream>
#include "MaxSubSeqSum.h"
#include <random>
#include <ctime>

using namespace std;

const int N = 10;        // the array size

typedef int (*pfunc)(int a[], int);

void test(pfunc pf, int a[], int sz)
{
    clock_t start, stop;
    int ret;
    start = clock();
    ret = pf(a, sz);
    stop = clock();
    cout << "the max subsequence sum: " << ret << endl;
    cout << (stop - start)/CLOCKS_PER_SEC << "s.\n";
}

int main()
{
    default_random_engine e;
    uniform_int_distribution<int> u(-1000, 0);
    int a[N];
    for (int i = 0; i < N; ++i)
        a[i] = u(e);

    for (int i = 0; i < N; ++i)
        cout << a[i] << " ";
    cout << endl;

    test(maxSubSeqSum1, a, N);
    test(maxSubSeqSum2, a, N);
    test(maxSubSeqSum3, a, N);
    test(maxSubSeqSum4, a, N);

    return 0;
}
