#include <iostream>
#include "LinkedListSort.h"
using namespace std;

int main()
{
    LinkedListSort s;
    for (int i = 18; i > 0; --i)
        s.push(i);
    s.print();
    cout << endl;
    cout << "After sort:\n";
    s.bottomUpSort();
    s.print();
    return 0;
}
