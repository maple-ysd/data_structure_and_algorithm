#include <iostream>
#include "BoyerMoore.h"

using namespace std;

int main()
{
    BoyerMoore bm("abca");
    string str = "bgcfdsabcnfhkabcanvckj";
    int i = bm.search(str);
    cout << i << ": "<< str.substr(i, 4) << endl;
    return 0;
}
