#include <iostream>
#include <stack>

using namespace std;
const int N = 10;
// ����Ԫ����˳��ѹ��ջ�С�ѹջ�����У���һѭ���ж�ջ��Ԫ���������Ԫ���Ƿ���ȣ�����ȣ�����ջ��Ԫ�أ���������Ԫ�غ��ƣ��ظ�������
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
