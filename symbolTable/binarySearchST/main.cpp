#include <iostream>
#include "binarySearchST.h"

using namespace std;

int main()
{
    binarySearchST st;
    for (int i = 0; i < 26; ++i)
    {
        char ch = 'a' + i;
        string str = "";
        st.put(str + ch, i);
    }
    for (auto x : st)
        cout << x.first << " " << x.second << endl;
    cout << endl;
    st.Delete("a");
    st.Delete("b");
    for (auto x : st)
        cout << x.first << " " << x.second << endl;

    cout << endl;
    string str = "";
    cout << st.get(str + 'm') << endl;
    return 0;
}
