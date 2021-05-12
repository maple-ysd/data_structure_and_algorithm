#include <iostream>
#include "classicalRedBlackTree.h"
using namespace std;

int main()
{
    classicalRedBlackTree<int, int> rbtree;
    for (int i = 1; i <= 10; ++i)
        rbtree.insert(i, i);
    // 通过前中序给出树的形状，后续验证
    // 测试删除
    rbtree.remove(4);
    rbtree.remove(9);
    rbtree.remove(10);
    cout << " preorder traversal: ";
    rbtree.preOrderTraversal();
    cout << endl;
    cout << "  inorder traversal: ";
    rbtree.inOrderTraversal();
    cout << endl;
    cout << "postorder traversal: ";
    rbtree.postOrderTraversal();
    cout << endl;
    return 0;
}
