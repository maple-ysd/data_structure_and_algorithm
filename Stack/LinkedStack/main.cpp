#include <iostream>
#include "LinkedStack.h"
using namespace std;

int main()
{
    LinkedStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    if (!s.empty())
        s.pop();
    cout << s.getTop() << endl;
    return 0;
}
