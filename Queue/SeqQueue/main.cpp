#include <iostream>
#include "SeqQueue.h"
using namespace std;

int main()
{
    SeqQueue<int> sq;
    if (sq.empty())
    {
        sq.push(1);
        sq.push(2);
        sq.pop();
        sq.push(3);
        sq.push(4);
    }
    cout << "size: " << sq.size() << " front: " << sq.getFront() << " back: " << sq.getBack() << endl;
    return 0;
}
