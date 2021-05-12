#include <iostream>
#include <string>
#include <cmath>
#include "Calculator.h"
using namespace std;

int main()
{
    Calculator cal;
    string str;
    cout << "want to start(q to quit)?\n";
    while (cin >> str && (str[0] == 'y' || str[0] == 'Y'))
    {
        cin.get();      // deal with '\n' after cin
        cal.getInput();
        cal.calculate();
        cout << "result:" << cal.getResult() << endl;
        cout << "want to continue(q to quit)?\n";
    }
    return 0;
}
