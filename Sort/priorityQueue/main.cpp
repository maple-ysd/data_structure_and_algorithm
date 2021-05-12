#include <iostream>
#include "priorityQueue.h"
#include "indexMinPriorityQueue.h"
using namespace std;

int main()
{
    priorityQueue q;
    q.push(5);
    q.push(6);
    q.push(4);
    q.push(8);
    q.push(3);
    int k = q.size();
    for (int i = 0; i < k; ++i)
    {
        cout << q.top() << " ";
        q.pop();
    }
    if (q.empty())
        cout << "\nover\n";

    // indexMinPriorityQueue
    indexMinPriorityQueue iq(10);
    iq.insert(1, 20);
    iq.insert(7, 50);
    iq.insert(8, 80);
    iq.insert(4, 30);
    iq.insert(5, 40);

    int cnt = iq.size();
    for (int i = 0; i < cnt; ++i)
    {
        cout << iq.minIndex() << ": " << iq.minElem() << endl;
        iq.deleteMin();
    }
    if (iq.empty())
        cout << "\nover\n";
    return 0;
}
