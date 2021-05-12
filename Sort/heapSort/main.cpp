#include <iostream>
#include <random>
#include <ctime>
#include "heapSort.h"
using namespace std;

const int N = 100;
int arr[N + 1];
void print(int (&arr)[N + 1])
{
    for (int i = 1; i <= N; ++i)
        cout << arr[i] << " ";
    cout << endl;
}
int main()
{
    default_random_engine e(time(0));
    uniform_int_distribution<int> u(0, 1000);
    for (int i = 1; i <= N; ++i)
        arr[i] = u(e);
    print(arr);
    heapSort(arr, N);
    print(arr);

    for (int i = 0; i <= N + 1; ++i)
        arr[i] = u(e);
    for (auto x : arr)
        cout << x << " ";
    cout << endl;
    heapSort2(arr, N + 1);
    for (auto x : arr)
        cout << x << " ";
    cout << endl;
    return 0;
}
