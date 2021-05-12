#include <iostream>
#include "SeqStack2.h"
using namespace std;

int main()
{
    cout << "ok here?.\n";
    SeqStack2<int> s;
    cout << "ok here?.\n";
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    if (!s.empty())
        s.pop();
    cout << s.getTop() << " " << s.size() << endl;
    return 0;
}
