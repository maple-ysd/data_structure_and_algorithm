#include <iostream>
#include <fstream>
#include "quick3.h"
using namespace std;

int main()
{
    ifstream fin("test.txt");

    vector<string> arr;
    string str;
    while (fin >> str)
        arr.push_back(str);
    for (auto s : arr)
        cout << s << endl;
    cout << "after sorted:\n";
    quick3(arr);
    cout << "Done.\n";

    for (auto s : arr)
        cout << s << endl;
    return 0;
}
