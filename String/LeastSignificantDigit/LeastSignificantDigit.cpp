#include "LeastSignificantDigit.h"
using namespace std;

void lsdSort(vector<string> &arr, int n)
{
    int alphabetSize = 128;
    string auxArr[arr.size()];

    for (int digit = n - 1; digit >= 0; --digit)
    {
        // count frequency
        int count[alphabetSize + 1] = {0};
        for (int i  = 0; i < arr.size(); ++i)
        {
            int index = arr[i][digit];
            ++count[index + 1];
        }

        // frequency -> indices
        for (int i = 0; i < alphabetSize; ++i)
            count[i + 1] += count[i];

        //
        for (int i = 0; i < arr.size(); ++i)
        {
            int index = arr[i][digit];
            auxArr[count[index]++] = arr[i];
        }

        for (int i = 0; i < arr.size(); ++i)
            arr[i] = auxArr[i];
    }
}
