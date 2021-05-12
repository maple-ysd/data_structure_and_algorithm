#include <iostream>
#include "sparseVector.h"
#include "sparseMatrix.h"
using namespace std;

//int main()
//{
//    sparseVector s(10);
//    s.insert(2, 10);
//    s.insert(3, 5);
//    s.insert(5, 20);
//    s.insert(1, 1);
//    s.insert(1, 5);
//    s.print();
//    cout << endl;
//
//    s.remove(1);
//    double arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//    cout << s.dot(arr, 10) << endl;
//    (s + s).print();
//    cout << endl;
//    cout << s * s << endl;
//    return 0;
//}


int main()
{
    sparseMatrix s(2, 2);
    s.insert(0, 0, 5);
    s.insert(0, 1, 4);
    s.insert(1, 0, 4);
    s.insert(1, 1, 5);
    s.print();
    s.remove(0, 0);
    s.print();
    cout << s.get(1, 1) << endl;
    (s + s).print();
    (s * s).print();
    sparseVector rhs(2);
    rhs.insert(0, 1);
    rhs.insert(1, 2);
    (s * rhs).print();
    cout << endl;
    return 0;
}
