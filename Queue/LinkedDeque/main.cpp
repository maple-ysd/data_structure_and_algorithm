#include <iostream>
#include "LinkedDeque.h"
using namespace std;

int main()
{
    LinkedDeque<int> s;
    for (int i = 0; i < 5; ++i)
        s.pushLeft(i);
    for (int i = 5; i < 10; ++i)
        s.pushRight(i);
    s.print();
    cout << endl;
    s.popLeft();
    s.popRight();
    s.print();
    cout << endl;
    cout << "size: " << s.size() << endl;
    cout << s.popLeft() << " " << s.popRight() << endl;
    return 0;
}
