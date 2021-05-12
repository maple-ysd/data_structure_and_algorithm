#include <iostream>
#include "Set.h"
using namespace std;

int main()
{
    Set<int> s;

    for (int i = 0; i < 100; ++i)
        s.add(i);
    for (auto x : s.keys())
        cout << x << " ";
    cout << endl;

    s.remove(40);
    s.remove(50);
    s.remove(60);

    s.deleteMax();
    s.deleteMin();

    for (auto x : s.keys())
        cout << x << " ";
    cout << endl;

    cout << s.rank(11) << endl;
    cout << s.rank(41) << endl;
    cout << s.rank(51) << endl;
    cout << s.rank(61) << endl;
    cout << endl;

    cout << s.select(11) << endl;
    cout << s.select(41) << endl;

    cout << endl;
    cout << s.Max() << endl;
    cout << s.Min() << endl;
    return 0;
}
