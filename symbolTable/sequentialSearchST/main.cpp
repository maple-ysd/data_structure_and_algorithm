#include <iostream>
#include "sequentialSearchST.h"
using namespace std;

int main()
{
    sequentialSearchST st;
    for (int i = 0; i < 26; ++i)
    {
        char ch = 'a' + i;
        string str = "";
        st.put(str + ch, i);
    }
    for (auto x : st)
        cout << x.key << " " << x.value << endl;

    st.Delete("a");
    st.Delete("b");
    for (auto x : st)
        cout << x.key << " " << x.value << endl;
    return 0;
}
