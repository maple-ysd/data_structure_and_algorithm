#include <iostream>
#include "Steque.h"
using namespace std;

int main()
{
    Steque<int> s;
    for (int i = 0; i < 5; ++i)
        s.push(i);
    for (int i = 5; i < 10; ++i)
        s.enque(i);
    s.print();
    cout << endl;
    s.pop();
    s.pop();
    cout << "After erase the first two numbers:\n";
    s.print();
    cout << endl;
    cout << "front: " << s.front() << "; back: " << s.back() << endl;
    return 0;
}
