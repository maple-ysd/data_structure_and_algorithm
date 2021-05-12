#include <iostream>
#include "hashSet.h"
using namespace std;

int main()
{
    hashSet<int> hs;
    for (int i = 0; i < 100; ++i)
        hs.insert(i);

    hs.remove(50);
    hs.remove(40);
    hs.remove(60);

    for (auto x : hs.keys())
        cout << x << " ";
    cout << endl;
    return 0;
}
