#include <iostream>

using namespace std;

void printCommon(int arr1[], int arr2[], int N)
{
    for (int i = 0, j = 0; i < N && j < N;)
    {
        if (arr1[i] < arr2[j])
            ++i;
        else if (arr1[i] > arr2[j])
            ++j;
        else
        {
            cout << arr1[i++] << " ";
            ++j;
        }
    }
}

int main()
{
    int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
    int arr2[10] = {0, 1, 2, 4, 5, 6, 7, 8, 10, 11 };
    printCommon(arr1, arr2, 10);
    return 0;
}
