#include <iostream>
#include "QuickFind.h"
#include "QuickUnion.h"
#include "WeightedQuickUnion.h"
#include "QuickUnionCompression.h"
#include "WeightedQuickUnionCompression.h"
#include "WeightedQuickUnionByHeight.h"
using namespace std;

int main()
{
    const int N = 10;
    int id[8][2] = { 9, 0,  3, 4,  5, 8,     7, 2,     2, 1,     5, 7,     0, 3,     4, 2 };
    // QuickFind test
    QuickFind QF(N);
    for (int i = 0; i < 8; ++i)
    {
        if (QF.connected(id[i][0], id[i][1])) continue;
        QF.Union(id[i][0], id[i][1]);
        cout << id[i][0] << " + " << id[i][1] << " ";
    }
    cout << endl;

    // QuickUnion test
    QuickUnion QU(N);
    for (int i = 0; i < 8; ++i)
    {
        if (QU.connected(id[i][0], id[i][1])) continue;
        QU.Union(id[i][0], id[i][1]);
        cout << id[i][0] << " + " << id[i][1] << " ";
    }
    cout << endl;

    // WeightedQuickUnion test
    WeightedQuickUnion WQU(N);
    for (int i = 0; i < 8; ++i)
    {
        if (WQU.connected(id[i][0], id[i][1])) continue;
        WQU.Union(id[i][0], id[i][1]);
        cout << id[i][0] << " + " << id[i][1] << " ";
    }
    cout << endl;

    // QuickUnionCompression test
    QuickUnionCompression QUC(N);
    for (int i = 0; i < 8; ++i)
    {
        if (QUC.connected(id[i][0], id[i][1])) continue;
        QUC.Union(id[i][0], id[i][1]);
        cout << id[i][0] << " + " << id[i][1] << " ";
    }
    cout << endl;

    // WeightedQuickUnionCompression test
    WeightedQuickUnionCompression WQUC(N);
    for (int i = 0; i < 8; ++i)
    {
        if (WQUC.connected(id[i][0], id[i][1])) continue;
        WQUC.Union(id[i][0], id[i][1]);
        cout << id[i][0] << " + " << id[i][1] << " ";
    }
    cout << endl;


    // WeightedQuickUnionByHeight test
    WeightedQuickUnionByHeight WQUH(19);
    int arr[16][2] = { {0, 1}, {0, 2}, {0, 3}, {6, 7}, {8, 9}, {6, 8}, {0, 6}, {10, 11}, {10, 12}, {10, 13}, {10, 14}, {10, 15}, {10, 16}, {10, 17}, {10, 18}, {0, 10} };
    for (int i = 0; i < 16; ++i)
    {
        if (WQUH.connected(arr[i][0], arr[i][1])) continue;
        WQUH.Union(arr[i][0], arr[i][1]);
    }
    cout << "components: " << WQUH.count() <<  ", expected: 3.\n";
    cout << "Maximum height: " << WQUH.maxHeight << ", expected: equal or less than 5 for N = 19, (lg19) = 5.\n";
    return 0;
}
