#include <iostream>
#include <string>
#include <fstream>
#include "Regex.h"
using namespace std;

int main()
{
    Regex grep("(.*AB[A-Z].*)");

    ifstream fin("test.txt");
    string line;
    while (getline(fin, line))
    {
        if (grep.recognize(line))
            cout << line << endl;
    }
    cout << "Done\n";
    return 0;
}
