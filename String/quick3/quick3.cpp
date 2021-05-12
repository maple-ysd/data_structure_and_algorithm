#include "quick3.h"
using namespace std;

void quick3(vector<string> &vs, int lo, int hi, int digit);

void quick3(vector<string> &vs)
{
    quick3(vs, 0, vs.size() - 1, 0);
}

void quick3(vector<string> &vs, int lo, int hi, int digit)
{
    if (lo >= hi) return;

    int lt = lo;
    int gt = hi;

    int pivot = -1;
    if (digit < vs[lo].size())
        pivot = vs[lo][digit];

    int i = lo + 1;

    while (i <= gt)
    {
        int currChar = -1;
        if (digit < vs[i].size())
            currChar = vs[i][digit];

        if (currChar < pivot)
            std::swap(vs[lt++], vs[i++]);
        else if (currChar > pivot)
            std::swap(vs[gt--], vs[i]);
        else
            ++i;
    }

    quick3(vs, lo, lt - 1, digit);
    if (pivot >= 0)
        quick3(vs, lt, gt, digit + 1);
    quick3(vs, gt + 1, hi, digit);
}
