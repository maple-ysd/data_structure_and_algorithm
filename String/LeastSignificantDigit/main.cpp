#include <iostream>
#include <fstream>
#include "LeastSignificantDigit.h"
using namespace std;

int main()
{
    ifstream fin("test.txt");   // ���ʳ��Ⱦ�Ϊ5

    vector<string> arr;
    string str;
    while (fin >> str)
        arr.push_back(str);
    for (auto s : arr)
        cout << s << endl;

    lsdSort(arr, 5);

    for (auto s : arr)
        cout << s << endl;
    return 0;
}
