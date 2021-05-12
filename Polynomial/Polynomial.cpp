#include <iostream>
#include <cmath>
#include <ctime>
#include "Polynomial.h"

using namespace std;

//using namespace std;
// f = a0 + a1 * x + a2 * x^2 + ...
double f1(int n, double a[], double x)
{
    double ret = a[0];
    for (int i = 1; i <= n; ++i)
        ret += a[i] * pow(x, i);
    return ret;
}
// f = a0 + (a1 + (a2 + ... + (an-1 + (an)) * x ...) * x)
double f2(int n, double a[], double x)
{
    double ret = a[n];
    for (int i = n; i > 0; --i)
        ret = a[i-1] + ret * x;
    return ret;
}

void test(int n, double a[], double x, pfunc pf)
{
    clock_t start, stop;
    double duration;
    start = clock();
    pf(n, a, x);
    stop = clock();
    duration = (stop - start) / CLOCKS_PER_SEC;
    cout << "duration = " << duration << "s.\n";
}

void test(int n, double a[], double x, pfunc pf, double called_times)
{
    clock_t start, stop;
    double duration;         // in seconds
    int i;
    start = clock();
    for (i = 0; i < called_times; ++i)
        pf(n, a, x);
    stop = clock();
    duration = (stop - start) / CLOCKS_PER_SEC / called_times;
    cout << "ticks = " << stop - start << "; duration = " << duration << "s.\n";
}
