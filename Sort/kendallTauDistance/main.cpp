#include <iostream>
#include "kendallTauDistance.h"
using namespace std;

int main()
{
    int arr1[7] = {0, 3, 1, 6, 2, 5, 4};
    int arr2[7] = {1, 0, 3, 6, 4, 2, 5};
    cout << kendallTauDistance(arr1, arr2, 7) << endl;
    cout << kendallTauDistance2(arr1, arr2, 7) << endl;
    return 0;
}
