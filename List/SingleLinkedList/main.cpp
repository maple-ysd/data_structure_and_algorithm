#include <iostream>
#include "SingleLinkedList.h"
using namespace std;

int main()
{
    SingleLinkedList s1, s2;
    s1.Create(5);
    if (!s1.IsEmpty())
        s1.Print();
    cout << endl;

    s2.PushBack(3);
    s2.PushFront(1);
    s2.Insert(2, 2);
    s2.Print();
    cout << endl;

    s2.PushBack(4);
    s2.PushBack(4);
    s2.PushBack(4);
    s2.PushBack(5);
    s2.PushBack(4);
    s2.Print();
    cout << endl;

    s2.PopBack();
    s2.PopFront();
    s2.Delete(2);
    s2.Remove(4);
    s2.Print();
    cout << endl;

    cout << s2.GetLength() << endl;
    return 0;
}
