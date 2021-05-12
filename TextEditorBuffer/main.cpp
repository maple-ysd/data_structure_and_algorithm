#include <iostream>
#include "TextEditorBuffer.h"
using namespace std;

int main()
{
    TextEditorBuffer s;
    for (int i = 0; i < 10; ++i)
        s.insert('a' + i);
    s.left(5);
    s.right(3);
    cout << s.Delete() << endl;
    return 0;
}
