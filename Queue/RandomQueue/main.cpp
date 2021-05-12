#include <iostream>
#include "RandomQueue.h"
using namespace std;

int main()
{
    RandomQueue<int> s;
    for (int i = 0; i < 4; ++i)
        for (int j = 1; j <= 13; ++j)
            s.enqueue(j);

    for (int i = 0; i < 4; ++i)
    {
        cout << s.size() << ": ";
        for (int j = 1; j <= 13; ++j)
            cout << s.sample() << " ";
        cout << endl;

    }
    cout << endl;
    for (int i = 0; i < 4; ++i)
    {
        cout << s.size() << ": ";
        for (int j = 1; j <= 13; ++j)
            cout << s.dequeue() << " ";
        cout << endl;
    }
    cout << endl;
    // test member function print()
    for (int i = 0; i < 10; ++i)
        s.enqueue(i);
    for (int i = 0; i < 5; ++i)
    {
        s.print();
        cout << endl;
    }
    return 0;
}
