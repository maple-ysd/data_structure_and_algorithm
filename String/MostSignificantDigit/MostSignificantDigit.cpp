#include <iostream>
#include "MostSignificantDigit.h"
using namespace std;

void msdSort(vector<string> &vs, string aux[], int lo, int hi, int digit);
void insertSort(vector<string> &vs, int lo, int hi, int digit);
bool Less(string str1, string str2, int digit);

static const int cutoff = 10;
static const int alphabetSize = 128;

void msdSort(vector<string> &vs)
{
    string auxArr[vs.size()];
    msdSort(vs, auxArr, 0, vs.size() - 1, 0);
}

void msdSort(vector<string> &vs, string auxArr[], int lo, int hi, int digit)
{
    // 避免大量重复字符串从而进入死循环
    bool flag = true;
    for (int i = lo; i <= hi; ++i)
    {
        if (digit < vs[i].size())
        {
            flag = false;
            break;
        }
    }
    if (flag) return;

    if (lo + cutoff >= hi)
    {
        insertSort(vs, lo, hi, digit);
        return;
    }
    // compute frequency
    int count[alphabetSize + 1] = {0};
    for (int i = lo; i <= hi; ++i)
    {
        int index = 1;
        if (digit < vs[i].size())
            index = vs[i][digit] + 1;
        ++count[index];
    }
    // frequency -> indices
    for (int i = 0; i < alphabetSize; ++i)
        count[i + 1] += count[i];
    //
    for (int i = lo; i <= hi; ++i)
    {
        int index = 0;
        if (digit < vs[i].size())
            index = vs[i][digit];
        auxArr[count[index]++] =  vs[i];
    }
    //
    for (int i = lo; i <= hi; ++i)
    {
        vs[i] = auxArr[i - lo];
    }

    msdSort(vs, auxArr, lo, lo + count[0] - 1, digit + 1);
    for (int i = 1; i < alphabetSize; ++i)
        msdSort(vs, auxArr, lo + count[i - 1], lo + count[i] - 1, digit + 1);
}

void insertSort(vector<string> &vs, int lo, int hi, int digit)
{
    for (int i = lo; i <= hi; ++i)
    {
        string temp = vs[i];
        int j;
        for (j = i; j > lo && Less(temp, vs[j - 1], digit); --j)
            vs[j] = vs[j - 1];
        vs[j] = temp;
    }
}

bool Less(string str1, string str2, int digit)
{
    for (int i = digit; i < min(str1.size(), str2.size()); ++i)
    {
        if (str1[i] < str2[i]) return true;
        else if (str1[i] > str2[i]) return false;
    }
    return str1.size() < str2.size();
}
