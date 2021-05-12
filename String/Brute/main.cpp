#include <iostream>
#include <string>
using namespace std;

int main()
{
    string txt("bgcfdsabcnfhkabcanvckj");
    string pat("abca");
    int M = pat.size();
    int N = txt.size();
    int i, j;
    for (i = 0, j = 0; i <= N - M && j < M; ++i)
    {
        if (txt[i] == pat[j]) ++j;
        else
        {
            i -= j;
            j = 0;
        }
    }
    if (j == M)
        cout << i - M << endl;
    else
        cout << N << endl;
    return 0;
}
