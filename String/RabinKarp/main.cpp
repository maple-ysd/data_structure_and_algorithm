#include <iostream>
#include "RabinKarp.h"

using namespace std;

int main()
{
    RabinKarp rk("abca");
    string str = "bgcfdsabcnfhkabcanvckj";
    int i = rk.search(str);
    cout << i << ": "<< str.substr(i, 4) << endl;
    return 0;
}
