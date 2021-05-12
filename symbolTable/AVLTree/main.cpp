#include <iostream>
#include "AVLTree.h"
using namespace std;

int main()
{
    AVLTree<int, int> avltree;
    for (int i = 1; i <= 10; ++i)
        avltree.insert(i, i);
//    avltree.insert(5, 5);
//    avltree.insert(2, 2);
//    avltree.insert(7, 7);
//    avltree.insert(20, 20);
//    avltree.insert(6, 6);
//    avltree.insert(3, 3);
//    avltree.insert(1, 1);
//    avltree.insert(30, 30);
//    avltree.insert(40, 40);
//    avltree.insert(50, 50);
    // 通过前中序给出树的形状，后续验证
    // 测试删除
    avltree.remove(4);
    avltree.remove(9);
    avltree.remove(10);
    cout << " preorder traversal: ";
    avltree.preOrderTraversal();
    cout << endl;
    cout << "  inorder traversal: ";
    avltree.inOrderTraversal();
    cout << endl;
    cout << "postorder traversal: ";
    avltree.postOrderTraversal();
    cout << endl;
    return 0;
}
