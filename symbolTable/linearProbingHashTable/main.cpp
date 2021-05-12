#include <iostream>
#include "linearProbingHashTable.h"
using namespace std;

int main()
{
    linearProbingHashTable<int, int> ht(100);
    for (int i = 1; i < 1000000000; i *= 2)
        ht.insert(i, i);
    ht.print();
    cout << endl;
    cout << ht.find(1024) << endl;

    cout << ht.size() << endl;
    ht.Delete(1024);
    if (ht.find(1024))
        cout << ht.find(1024)<< endl;
    else
        cout << "already deleted.\n";

    cout << ht.size() << endl;
    ht.print();
    cout << endl;
    return 0;
}
