#include <iostream>
#include "Polynomial.h"

//#define MAXN 10       // ����ʽ����
//#define MAXK 1e8        // �ظ����ô���

const int MAXN = 10;
const int MAXK = 1e8;       // a better way in C++;

using namespace std;

int main()
{
    double a[MAXN];     // ����ʽϵ��
    for (int i = 0; i < MAXN; ++i)
        a[i] = i;

    test(MAXN - 1, a, 1.1, f1, MAXK);
    test(MAXN - 1, a, 1.1, f2, MAXK);
    return 0;
}
