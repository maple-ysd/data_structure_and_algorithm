#include <iostream>
#include <random>
#include <ctime>
#include "mergeSort.h"

using namespace std;

int main()
{
    const int N = 20;
    default_random_engine e(time(0));
    uniform_int_distribution<int> u(1, 20);
    int arr[N];
    int T = 10;
    for (int k = 0; k < T; ++k)
    {
        for (int i = 0; i < N; ++i)
            arr[i] = u(e);
        for (auto x : arr)
            cout << x << " ";
        cout << endl;

        mergeSort4(arr, N);
        cout << "after merge sort:\n";
        for (auto x : arr)
            cout << x << " ";
        cout << endl;
    }

    cout << endl;
    return 0;
}
