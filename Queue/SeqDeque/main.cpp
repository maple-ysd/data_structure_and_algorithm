#include <iostream>
#include "SeqDeque.h"
using namespace std;

int main()
{
    SeqDeque<int> s;
    for (int i = 0; i < 5; ++i)
    {
        s.pushLeft(i);
        cout << s.size() << ": ";
        s.print();
        cout << endl;
    }
    for (int i = 5; i < 10; ++i)
    {
        s.pushRight(i);
        cout << s.size() << ": ";
        s.print();
        cout << endl;
    }
    s.print();
    cout << endl;
    for (int i = 0; i < 5; ++i)
    {
        s.popLeft();
        cout << s.size() << ": ";
        s.print();
        cout << endl;
        s.popRight();
        cout << s.size() << ": ";
        s.print();
        cout << endl;
    }
    return 0;
}
