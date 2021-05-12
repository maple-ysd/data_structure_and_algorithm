#include <iostream>
#include "Polynomial.h"

using namespace std;

int main()
{
    Poly p1, p2, sum, product1, product2;
    cout << "please enter the polynomial(in following format):n c1 e1 c2 e2 c3 e3 ...\n";
    p1 = ReadPoly(cin);
    cout << "polynomial p1:\n";
    Print(p1);
    cout << endl;
    cout << "please enter the polynomial(in following format):\nn c1 e1 c2 e2 c3 e3 ...\n";
    p2 = ReadPoly(cin);
    cout << "polynomial p2:\n";
    Print(p2);
    cout << endl;
    sum = AddPoly(p1, p2);
    cout << "polynomial sum:\n";
    Print(sum);
    cout << endl;
    product1 = Mult1(p1, p2);
    cout << "polynomial product1:\n";
    Print(product1);
    cout << endl;
    product2 = Mult2(p1, p2);
    cout << "polynomial product2:\n";
    Print(product2);
    cout << endl;

    destroy(p1);
    destroy(p2);
    destroy(sum);
    destroy(product1);
    destroy(product2);
    return 0;
}
