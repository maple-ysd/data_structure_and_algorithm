#include <iostream>
#include <fstream>
#include "MostSignificantDigit.h"
using namespace std;

int main()
{
    ifstream fin("test.txt");   // 单词长度均为5

    vector<string> arr;
    string str;
    while (fin >> str)
        arr.push_back(str);
    for (auto s : arr)
        cout << s << endl;
    cout << "after sorted:\n";
    msdSort(arr);
    cout << "Done.\n";

    for (auto s : arr)
        cout << s << endl;
    return 0;
}
