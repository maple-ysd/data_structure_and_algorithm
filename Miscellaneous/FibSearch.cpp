#include <iostream>

using namespace std;
// (FIBn - 1) = (FIBn-1 -1) + 1 + (FIBn-2 - 1)
//                prev       mid     post
int FibSearch(double arr[], int N, double val)
{
    int Fib1 = 0;
    int Fib2 = 1;
    int temp;
    while (Fib2 - 1 < N)
    {
        temp = Fib2;
        Fib2 = Fib2 + Fib1;
        Fib1 = temp;
    }
    for (int i = N; i < Fib2 -1; ++i)
        arr[i] = arr[N - 1];

    int low = 0;
    int high = N - 1;
    int mid;
    while (low <= high)
    {
        mid = low + Fib1 - 1;
        if (arr[mid] < val)
        {
            low = mid + 1;
            temp = Fib2 - Fib1;
            Fib2 = temp;
            Fib1 = Fib1 - temp;
        }
        else if (arr[mid] > val)
        {
            high = mid - 1;
            temp = Fib1;
            Fib1 = Fib2 - Fib1;
            Fib2 = temp;
        }
        else
        {
            if (mid < N)
                return mid;
            else if (mid >= N)
                return N - 1;
        }
    }
    return -1;

}

int main()
{
    const int N = 10;
    double arr[N] = { -5, -3, -2, -1, 0, 1, 3, 5, 7, 9 };
    int index = FibSearch(arr, N, 9);
    cout << index << ": " << arr[index] << endl;
    return 0;
}
