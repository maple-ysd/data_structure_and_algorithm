#ifndef CALCULATOR_H_
#define CALCULATOR_H_

//  realize a calculator
//  +, -, *, /, %, ^, ||,  !(factorial), sin, cos, tan, log, lg, ()

/*
    notice, when you mixed different symbols(trigonometric or logarithmic function) to calculate, please use parentheses
*/

/*  simplified expression of some symbols
    l: log based on 10
    n: ln based on e
    s: sin
    c: cos
    t: tan
    |: ||
    P: + for positive
    N: - for negative
    p : PI, 3.14159265358979323846
*/
#include <stack>
#include <vector>
#include <string>

class Calculator
{
    enum ABS_ODEVITY { ABS_ODD = 1, ABS_EVEN = 2 };     // just to know the half absolute symbol represents left or right
    // calculation symbol priority:(low->high) +-,  */%, positive/negative, ^(power), !(factorial), some functions, log, ln, sin, cos, tan...
    enum PRIO_LV
    {
        PRIO_LV0 = 0,
        PRIO_LV1 = 1,
        PRIO_LV2 = 2,
        PRIO_LV3 = 3,
        PRIO_LV4 = 4,
        PRIO_LV5 = 5,
        PRIO_LV6 = 6
    };
public:
    Calculator() { result = 0.0; }
    void getInput();                            // Enter infix expression to be calculated
    void formatInfix();
    int getPrior(char c);                       // get symble priority
    void getPostfix();                          // postfix expression conversion
    void calPostfix();                          // calculate postfix expression
    void calculate();                           // calculate process
    double getResult();                         // get calculation result
private:
    std::string infix;                          // infix expression
    bool check();                               // check roughly if input is valid
    std::vector<std::string> postfix;           // postfix expression
    std::stack<char> symStack;           // symble stack
    std::stack<double> figStack;                // figure stack
    std::string stdInfix;                       // formatted infix
    double result;
};


#endif // CALCULATOR_H_
