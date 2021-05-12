#include <iostream>
#include "SeqStack1.h"
using namespace std;

int main()
{
    SeqStack1<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.pop();
    cout << s.getTop() << " " << s.size() << endl;
    return 0;
}
