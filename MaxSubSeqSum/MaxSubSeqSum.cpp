#include "MaxSubSeqSum.h"

//
int maxSubSeqSum1(int a[], int N)
{
    int thisSum, maxSum = a[0];
    int i, j, k;
    for (i = 0; i < N; ++i)     // i is the start position of subsequence to be sumed
    {
        for (j = i; j < N; ++j) // j is the end position(included) of subsequence to be sumed
        {
            thisSum = 0;
            for (k = i; k <= j; ++k)    // thisSum is sum of subsequence from a[i] to a[j]
                thisSum += a[k];
            if (thisSum > maxSum)       // if thisSum is bigger than maxSum
                maxSum = thisSum;       // update maxSum
        }
    }
    return maxSum;
}
//
int maxSubSeqSum2(int a[], int N)
{
    int thisSum, maxSum = a[0];
    int i, j, k;
    for (i = 0; i < N; ++i)     // i is the start position of subsequence to be sumed
    {
        thisSum = 0;            // thisSum is sum of subsequence
        for (j = i; j < N; ++j) // j is the end position(included) of subsequence to be sumed
        {
            thisSum += a[j];    // for different j, just need to add a[j] to previous sum from a[i] to a[j-1]
            if (thisSum > maxSum)       // if thisSum is bigger than maxSum
                maxSum = thisSum;       // update maxSum
        }
    }
    return maxSum;
}

//
int max3(int a, int b, int c)
{
    if (a > b)
        return a > c ? a : c;
    else
        return b > c ? b : c;
}

int maxSubSeqSum3(int a[], int N)
{
    if (N == 1)
        return a[0];
    int maxLeftSum, maxRightSum;    // max sum of subsequence of left part, right part
    int maxLeftBorderSum, maxRightBorderSum;// max sum of subsequence of left part including a[mid-1]
                                            // max sum of subsequence of right part including a[mid]
    int leftBorderSum, rightBorderSum;

    int mid = N/2;          // separate the sequence into left and right parts;
    maxLeftSum = maxSubSeqSum3(a, mid);
    maxRightSum = maxSubSeqSum3(&a[mid], N - mid);

    // get the max sum of subsequence(crossing border(mid))
    // scanning for left part
    maxLeftBorderSum = a[mid-1]; leftBorderSum = 0;
    for (int i = mid - 1; i >= 0; i--)
    {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    // scanning for right part
    maxRightBorderSum = a[mid]; rightBorderSum = 0;
    for (int i = mid; i < N; ++i)
    {
        rightBorderSum += a[i];
        if (rightBorderSum> maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }

    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

//
int maxSubSeqSum4(int a[], int N)
{
    int maxSum, thisSum;
    thisSum = 0;
    maxSum = a[0];
    int i;
    for (i = 0; i < N; ++i)
    {
        thisSum += a[i];        // accumulation to right side
        if (thisSum > maxSum)
            maxSum = thisSum;   // update result maxSum
        else if (thisSum < 0)
            thisSum = 0;        // can not make sum of following subsequence greater, and then discard it
    }
    return maxSum;
}
