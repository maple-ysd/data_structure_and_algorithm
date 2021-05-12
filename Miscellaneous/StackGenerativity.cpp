#include <iostream>
#include <stack>

using namespace std;
const int N = 10;
// 所有元素依顺序压入栈中。压栈过程中，用一循环判断栈顶元素与待测试元素是否相等，若相等，弹出栈顶元素，将待测试元素后移，重复操作。
bool stackGenerativity(const int order[], const int test[])
{
    stack<int> s;
    int j = 0;

    for (int i = 0; i < N; ++i)
    {
        s.push(order[i]);
        for (; !s.empty() && s.top() == test[j]; ++j)   // don't forget !s.empty(), otherwise it will pass the boundary
            s.pop();
    }
    if (s.empty())
        return true;
    else
        return false;
}

int main()
{
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = i;
    int test[N];
    cout << "Enter a permutation of " << N << " numbers you want to test:\n";
    for (int i = 0; i < N; ++i)
        cin >> test[i];
    if (stackGenerativity(arr, test))
        cout << "this permutation can be generated.\n";
    else
        cout << "this permutation is invalid.\n";
    return 0;
}
