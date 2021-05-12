#include <iostream>
#include "separateChainingHashTable.h"
using namespace std;

int main()
{
    separateChainingHashTable<int, int> ht;
    for (int i = 1; i < 1000000000; i *= 2)
        ht.insert(i, i);
    cout << ht.find(1024)->value << endl;

    cout << ht.size() << endl;
    ht.Delete(1024);
    if (ht.find(1024))
        cout << ht.find(1024)->value << endl;
    else
        cout << "already deleted.\n";

    cout << ht.size() << endl;
    return 0;
}
