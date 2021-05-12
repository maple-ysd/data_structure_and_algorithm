#include <iostream>
#include "DoubleCircularLinkedList.h"
using namespace std;

int main()
{
    DoubleCircularLinkedList<int> s;
    for (int i = 0; i < 5; ++i)
        s.push_back(i);
    for (int i = 5; i <= 9; ++i)
        s.push_front(i);
    s.print();
    cout << endl;
    cout << "ok here ?\n";

    s.pop_back();
    s.pop_front();
    s.insertBefore(2, 22);
    s.insertAfter(8, 88);

    s.print();
    cout << endl;

    cout << "5th element: " << s.getElem(5) << "\nfirst element: " << s.front() << "\nlast element: " << s.back() << endl;

    return 0;
}
