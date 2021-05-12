#include <iostream>

using namespace std;
// 查找对应键值最小的索引并返回该索引
int binarySearch(int arr[], int elem, int low, int high)
{
    if (low > high) return - 1;
    else
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] < elem)
            return binarySearch(arr, elem, mid + 1, high);
        else if (arr[mid] > elem)
            return binarySearch(arr, elem, low, mid - 1);
        else
        {
            if (mid > 0 && arr[mid - 1] == elem)
                return binarySearch(arr, elem, low, mid - 1);
            else
                return mid;
        }
    }
}

int binarySearchIteration(int arr[], int elem, int low, int high)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] < elem)
            low = mid + 1;
        else if (arr[mid] > elem)
            high = mid - 1;
        else
        {
            if (mid > 0 && arr[mid - 1] == elem)
                high = mid - 1;
            else
                return mid;
        }
    }
    return -1;
}


int main()
{
    int arr[15] = { 1, 2, 3, 3, 3, 3, 3, 4, 6, 6, 7, 8, 9, 10, 11 };
    cout << binarySearch(arr, 3, 0, 14) << endl;
    cout << binarySearchIteration(arr, 3, 0, 14) << endl;
    return 0;
}
