#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>

typedef struct Node *Poly;
struct Node
{
    double coef;
    int expo;
    Node *next;
};
// read polynomial into Poly object
/*
format
n   c1 e1   c2 e2   c3 e3 ....
n is the number  of terms, c is coefficient, e is exponent
*/
Poly ReadPoly(std::istream &is);

// add polynomial p1, p2 and store the sum into ret
Poly AddPoly(Poly p1, Poly p2);

// multiply two polynomials
// each item of p1 times p2 and sum into ret by AddPoly method
Poly Mult1(Poly p1, Poly p2);
// each item of p1 times each item of p2 and then insert it into ret
Poly Mult2(Poly p1, Poly p2);

// print polynomial
void Print(Poly p);

// free the memory
void destroy(Poly p);

#endif // POLYNOMIAL_H_
