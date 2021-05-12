#include <iostream>
#include "KMP.h"

using namespace std;

int main()
{
    KMP kmp("abca");
    string str = "bgcfdsabcnfhkabcanvckj";
    int i = kmp.search(str);
    cout << str.substr(i, 4);
    return 0;
}
