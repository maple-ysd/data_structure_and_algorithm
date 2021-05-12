#include <iostream>
#include <cmath>
#include "Calculator.h"
#include <cctype>

using namespace std;
const double PI = 3.14159265358979323846;
// represents valid basic calculation symbols or their first character, eg s for sin, l for ln and log, P for const PI ---3.1415926...
string cstr = "+-*/%!^()|";
string abbr = "lsctP";
 bool Calculator::check()
{
    for (string::size_type i = 0; i < infix.size();)
    {
        if (isdigit(infix[i]) || infix[i] == '.')
        {
            ++i;
        }
        else if (cstr.find(infix[i]) != string::npos || isspace(infix[i]))
        {
            ++i;
        }
        else if (infix[i] == 'l' || infix[i] == 's' || infix[i] == 'c' || infix[i] == 't' || infix[i] == 'P')
        {
            switch(infix[i])
            {
                case 'l':
                    if (infix[i + 1] == 'o' && infix[i + 2] == 'g') { i += 3; break; }
                    else if (infix[i + 1] == 'n') { i += 2; break; }
                    else return false;
                case 's':
                    if (infix[i + 1] == 'i' && infix[i + 2] == 'n') { i += 3; break; }
                    else return false;
                case 'c':
                    if (infix[i + 1] == 'o' && infix[i + 2] == 's') { i += 3; break; }
                    else return false;
                case 't':
                    if (infix[i + 1] == 'a' && infix[i + 2] == 'n') { i += 3; break; }
                    else return false;
                case 'P':
                    if (infix[i + 1] == 'I') { i += 2; break; }
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Calculator::getInput()
{
    cout << "Please enter the infix expression you want to calculate:\n";
    getline(cin, infix);
    while (!check())
    {
        cout << "containing invalid input, please enter again:\n";
        getline(cin, infix);
    }
}
//
void Calculator::formatInfix()
{
    stdInfix = infix;
    // assume all of the characters are valid here...
    for (string::size_type i = 0; i < stdInfix.size(); ++i)
    {
        if (isspace(stdInfix[i]))
        {
            stdInfix.erase(i, 1);
            --i;
            continue;
        }
        if (stdInfix[i] == '+' || stdInfix[i] == '-')
        {
            // if +/- is the first character or - is just after '(', add 0 before - sign, change it into 0 +/- ... or (0 +/- ...
            if (i == 0 || stdInfix[i - 1] == '(' )
            {
                stdInfix.insert(i, 1, '0');
                ++i;        // pass the new added character
            }
            // if +/- means positive/negative, then replace it with P/N
            /* if (stdInfix[i - 1] == '+' || stdInfix[i - 1] == '-'|| stdInfix[i - 1] == '*' || stdInfix[i - 1] == '/'
                   || stdInfix[i - 1] == '%' || stdInfix[i - 1] == '^')
            */
            if (stdInfix[i - 1] != '!' && stdInfix[i - 1] != ')' && !isdigit(stdInfix[i - 1]))
            {
                if (stdInfix[i] == '+')
                    stdInfix.replace(i, 1, 1, 'P');
                else
                    stdInfix.replace(i, 1, 1, 'N');
            }
        }
        // if input number is like: 0. or .0, modify it into 0.0
        else if (stdInfix[i] == '.')
        {
            if (!isdigit(stdInfix[i - 1]))
            {
                stdInfix.insert(i, 1, '0');
                ++i;
            }
            else if (!isdigit(stdInfix[i + 1]))
            {
                stdInfix.insert(i + 1, 1, '0');
                ++i;
            }
        }
        // simplify some symbols: sin->s, cos->c, tan->t, log->l, ln->n
        else if (stdInfix[i] == 'l' || stdInfix[i] == 's' || stdInfix[i] == 'c' || stdInfix[i] == 't' || stdInfix[i] == 'P')
        {
            switch(stdInfix[i])
            {
            case 'l':
                if (stdInfix[i + 1] == 'n')
                {
                    stdInfix.replace(i, 2, 1, 'n');
                    break;
                }
            case 's':
            case 'c':
            case 't': stdInfix.erase(i + 1, 2); break;
            case 'P': stdInfix.replace(i, 2, 1, 'p'); break;
            }
        }
    }

}
// calculation symbol priority:(low->high) +-,  */%, positive/negative, ^(power), !(factorial), some functions, log, ln, sin, cos, tan...
int Calculator::getPrior(char c)
{
    switch(c)
    {
        case '+':
        case '-': return PRIO_LV1;
        case '*':
        case '/':
        case '%': return PRIO_LV2;
        case 'P':
        case 'N': return PRIO_LV3;
        case '^': return PRIO_LV4;
        case '!': return PRIO_LV5;
        case 'l':
        case 'n':
        case 's':
        case 'c':
        case 't': return PRIO_LV6;
        case '|':
        case '(': return PRIO_LV0;  // here means after pushed into stack
    }
    exit(EXIT_FAILURE);
}
void Calculator::getPostfix()
{

    int absNumber = ABS_ODD;
    string tmp;
    postfix.clear();

    for (string::size_type i = 0; i < stdInfix.size(); ++i)
    {
        tmp = "";
        switch(stdInfix[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '!':
        case 'l':
        case 'n':
        case 's':
        case 'c':
        case 't':
        case 'P':
        case 'N':
          if (symStack.empty() || symStack.top() == '(' || symStack.top() == '|')
              symStack.push(stdInfix[i]);
          else
          {
              while (!symStack.empty() && (getPrior(symStack.top()) >= getPrior(stdInfix[i])))
              {
                  tmp += symStack.top();
                  postfix.push_back(tmp);
                  symStack.pop();
                  tmp = "";
              }
              symStack.push(stdInfix[i]);
          }
          break;
        case '|':
            if (absNumber == ABS_ODD)
            {
                symStack.push(stdInfix[i]);
                absNumber = ABS_EVEN;
            }
            else
            {
                while (!symStack.empty() && symStack.top() != '|')
                {
                    tmp += symStack.top();
                    postfix.push_back(tmp);
                    symStack.pop();
                    tmp = "";
                }
                if (!symStack.empty() && symStack.top() == '|')
                {
                    tmp += symStack.top();
                    postfix.push_back(tmp);
                    symStack.pop();
                    absNumber = ABS_ODD;
                }
            }
            break;
        case '(':
            symStack.push(stdInfix[i]);
            break;
        case ')':
            while (!symStack.empty() && symStack.top() != '(')
            {
                tmp += symStack.top();
                postfix.push_back(tmp);
                symStack.pop();
                tmp = "";
            }
            if (!symStack.empty() && symStack.top() == '(')
                symStack.pop();
            break;
        case 'p': tmp += 'p'; postfix.push_back(tmp); break;
        default:
            if (isdigit(stdInfix[i]))
            {
                tmp += stdInfix[i];
                while (i + 1 < stdInfix.size() && (isdigit(stdInfix[i + 1]) || stdInfix[i + 1] == '.'))
                {
                    tmp += stdInfix[i + 1];     // process continuous numbers
                    i++;
                }
            }
            postfix.push_back(tmp);
            break;
        }   // end switch
    }   // end for loop
    // process remaining part symStack
    while (!symStack.empty())
    {
        tmp = "";
        tmp += symStack.top();
        postfix.push_back(tmp);
        symStack.pop();
        tmp = "";
    }
}
void Calculator::calPostfix()
{
    string tmp;
    double num = 0;
    double op1, op2;

    for (vector<string>::size_type i = 0; i < postfix.size(); ++i)
    {
        tmp = postfix[i];
        if (isdigit(tmp[0]))
        {
            num = stod(tmp);
            figStack.push(num);
        }
        else if (postfix[i] == "p")
            figStack.push(PI);
        else
        {
            if (postfix[i] == "+")
            {
                if (!figStack.empty()) { op2 = figStack.top(); figStack.pop(); }
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(op1 + op2);
            }
            else if (postfix[i] == "-")
            {
                if (!figStack.empty()) { op2 = figStack.top(); figStack.pop(); }
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(op1 - op2);
            }
            else if (postfix[i] == "*")
            {
                if (!figStack.empty()) { op2 = figStack.top(); figStack.pop(); }
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(op1 * op2);
            }
            else if (postfix[i] == "/")
            {
                if (!figStack.empty()) { op2 = figStack.top(); figStack.pop(); }
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                if (op2 == 0) cout << "division by 0.\n";
                figStack.push(op1 / op2);
            }
            else if (postfix[i] == "%")
            {
                if (!figStack.empty()) { op2 = figStack.top(); figStack.pop(); }
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                if (op1 == 0) { cout << "x % 0.0\n"; exit(EXIT_FAILURE); }
                figStack.push(fmod(op1, op2));
            }
            else if (postfix[i] == "^")
            {
                if (!figStack.empty()) { op2 = figStack.top(); figStack.pop(); }
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(pow(op1, op2));
            }
            else if (postfix[i] == "P")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(op1);
            }
            else if (postfix[i] == "N")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(-1.0 * op1);
            }
            else if (postfix[i] == "!")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                if (op1 >= 0.0)
                {
                    if (op1 == 0) figStack.push(1.0);
                    else
                    {
                        double ret = 1;
                        for (int i = 1; i <= op1; ++i)
                            ret *= i;
                        figStack.push(ret);
                    }
                }
                else
                {
                    cout << "x!, x is negative.\n";
                    exit(EXIT_FAILURE);
                }
            }
            else if (postfix[i] == "s")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(sin(op1));
            }
            else if (postfix[i] == "c")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                figStack.push(cos(op1));
            }
            else if (postfix[i] == "t")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                if (fabs(cos(op1)) < 1.0E-12) { cout << "tan(x), x can not be equal to pi/2.\n"; exit(EXIT_FAILURE); }
                // here when the radian is between +/-3.14159265358 +/- 10^-9, we regard it as so-called pi
                figStack.push(tan(op1));
            }
            else if (postfix[i] == "l")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                if (op1 <= 0) { cout << "logx, x <= 0.\n"; exit(EXIT_FAILURE); }
                figStack.push(log10(op1));
            }
            else if (postfix[i] == "n")
            {
                if (!figStack.empty()) { op1 = figStack.top(); figStack.pop(); }
                if (op1 <= 0) { cout << "logx, x <= 0.\n"; exit(EXIT_FAILURE); }
                figStack.push(log(op1));
            }
        }
    }   // end for loop
    if (!figStack.empty())
        result = figStack.top();
    while (!figStack.empty())
        figStack.pop();
}
void Calculator::calculate()
{
    cout << "infix:" << infix << endl;
    formatInfix();
    cout << "formatted infix:" << stdInfix << endl;
    getPostfix();
    cout << "postfix:";
    for (auto x : postfix)
        cout << x << " ";
    cout << endl;
    calPostfix();

}
double Calculator::getResult()
{
    return result;
}
