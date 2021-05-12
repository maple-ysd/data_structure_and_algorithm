#include <iostream>
#include "nSum.h"

using namespace std;

int main()
{
    const int N = 10;
    int ar[N] = { 1, -1, -1, -3, 4, -3, -2, 2, -4, 3};
    int cnt = _2sum1(ar, N, -4);
    cout << cnt << endl;
    cnt = _2sum2(ar, N, -4);
    cout << cnt << endl;

    cout << endl;

    cnt = _3sum1(ar, N, 5);
    cout << cnt << endl;
    cnt = _3sum2(ar, N, 5);
    cout << cnt << endl;

    cnt = _3sum3(ar, N, 5);
    cout << cnt << endl;

    cout << endl;
    cnt = _4sum1(ar, N, 2);
    cout << cnt << endl;
    cnt = _4sum2(ar, N, 2);
    cout << cnt << endl;
    return 0;
}
