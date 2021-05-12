#include <iostream>
#include "SeqList.h"
using namespace std;

int main()
{
    SeqList s1, s2;
    InitSeqList(s1);
    InitSeqList(s2, 50);
    if (IsEmpty(s1))
    {
        for (int i = 0; i < 10; ++i)
            InsertSeqList(s1, i, i);
    }

    DisplaySeqList(s1);
    DelSeqList(s1, 5);
    DelSeqList(s1, 8);
    DisplaySeqList(s1);
    ClearSeqList(s1);
    DisplaySeqList(s1);

    if (IsEmpty(s2))
    {
        for (int i = 0; i < 50; ++i)
            InsertSeqList(s2, i, i);
    }
    InsertSeqList(s2, 0, 100);
    cout << GetLength(s2) << " " << s2.capacity << endl;

    return 0;
}
