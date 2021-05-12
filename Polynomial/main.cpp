#include <iostream>
#include "Polynomial.h"

//#define MAXN 10       // 多项式项数
//#define MAXK 1e8        // 重复调用次数

const int MAXN = 10;
const int MAXK = 1e8;       // a better way in C++;

using namespace std;

int main()
{
    double a[MAXN];     // 多项式系数
    for (int i = 0; i < MAXN; ++i)
        a[i] = i;

    test(MAXN - 1, a, 1.1, f1, MAXK);
    test(MAXN - 1, a, 1.1, f2, MAXK);
    return 0;
}
