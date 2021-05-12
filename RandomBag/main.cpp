#include <iostream>
#include "RandomBag.h"
using namespace std;

int main()
{
    RandomBag<int> s;
    for (int i = 0; i < 5; ++i)
        s.add(i);
    for (int i = 0; i < 5; ++i)
    {
        for (int x : s)
            cout << x << " ";
        cout << endl;
    }
    return 0;
}
