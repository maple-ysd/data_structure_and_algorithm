#include <iostream>
#include "separateChainingHashTableFixedSize.h"
using namespace std;

int main()
{
    separateChainingHashTableFixedSize<int, int> ht;
    for (int i = 1; i < 1000000000; i *= 2)
        ht.insert(i, i);
    cout << ht.find(1024)->value << endl;
    ht.Delete(1024);
    if (ht.find(1024))
        cout << ht.find(1024)->value << endl;
    else
        cout << "already deleted.\n";
    return 0;
}
