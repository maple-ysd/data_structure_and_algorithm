#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

// f = a0 + a1 * x + a2 * x^2 + ...
double f1(int n, double a[], double x);

// f = a0 + (a1 + (a2 + ... + (an-1 + (an)) * x ...) * x)
double f2(int n, double a[], double x);

// test which func is faster f1 or f2 ?
typedef double (*pfunc)(int n, double a[], double x);

void test(int n, double a[], double x, pfunc pf);   // called one time
// called several times;
void test(int n, double a[], double x, pfunc pf, double called_times);


#endif // POLYNOMIAL_H_
