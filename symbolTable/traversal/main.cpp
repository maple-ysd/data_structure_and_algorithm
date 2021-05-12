#include <iostream>
#include <string>
#include "traversal.h"
using namespace std;

int main()
{
    const int N = 10;
    string arrs[N];
    string s = "key";
    int arr[N] = {4, 1, 0, 2, 3, 7, 5, 6, 8, 9};
    for (int i = 0; i < N; ++i)
    {
        arrs[i] = s + to_string(arr[i]);
    }
    Node* root = buildTree(arrs, arr, N);
    cout << "preOrderTraversal:\n";
    preOrderTraversal(root);
    cout << endl;
    preOrderTraversal2(root);
    cout << endl;
    cout << endl;
    cout << "inOrderTraversal:\n";
    inOrderTraversal(root);
    cout << endl;
    inOrderTraversal2(root);
    cout << endl;
    cout << endl;
    cout << "postOrderTraversal:\n";
    postOrderTraversal(root);
    cout << endl;
    postOrderTraversal2(root);
    cout << endl;
    postOrderTraversal3(root);
    cout << endl;
    deleteTree(root);
    return 0;
}
