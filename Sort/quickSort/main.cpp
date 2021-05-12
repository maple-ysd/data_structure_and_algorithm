#include <iostream>
#include <random>
#include <ctime>
#include "quickSort.h"
using namespace std;

void print(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

//int main()
//{
//    const int N = 10;
//    const int T = 10;
//    default_random_engine e(time(0));
//
//    uniform_int_distribution<int> u(0, 100);
//    for (int i = 0; i < T; ++i)
//    {
//        //    bernoulli_distribution u(0.5);
//        int arr[N];
//        for (int i = 0; i < N; ++i)
//            arr[i] = u(e);
//        print(arr, N);
//        cout << "after sort:\n";
//        quickSortFast3Way(arr, N);
//        print(arr, N);
//        cout << endl;
//    }
////    cout << subArraySize0 << " " << subArraySize1 << " " << subArraySize2 << endl;
//    return 0;
//}


int main()
{
    const int N = 100000;
    const int T = 1000;
    int arr[N];
    default_random_engine e(time(0));
    uniform_int_distribution<int> u(0, 10000000);
    clock_t start = clock();
    for (int i = 0; i < T; ++i)
    {
        for (int i = 0; i < N; ++i)
            arr[i] = u(e);
        quickSort3Way(arr, N);

    }
    cout << (clock() - start) / CLOCKS_PER_SEC << endl;
    start = clock();
    for (int i = 0; i < T; ++i)
    {
        for (int i = 0; i < N; ++i)
            arr[i] = u(e);
        quickSortFast3Way(arr, N);

    }
    cout << (clock() - start) / CLOCKS_PER_SEC << endl;
    return 0;
}
