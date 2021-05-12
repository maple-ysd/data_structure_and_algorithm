#include <iostream>
#include "binarySearchTree.h"
using namespace std;

int main()
{
    binarySearchTree<int, int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.insert(i, i);
    }

    for (auto x : bst)
        cout<< x->key << " " << x->value << " " << x->Size << " " << "    ";
    cout << endl;
    cout << bst.select(5)->key << " " << bst.select(5)->value << endl;
    cout << bst.rank(6)<< " " << bst.rank(6)<< endl;
    cout << bst.Min()->key << " " << bst.Max()->key << endl;
    cout << bst.lowerBound(8)->key << " " << bst.upperBound(8)->key << endl;
    cout << endl;

    bst.deleteMin();
    bst.deleteMax();
    bst.Delete(5);
    for (auto x : bst)
        cout<< x->key << " " << x->value << " " << x->Size << " " << "    ";
    cout << endl;

    cout << bst.treeHeight() << endl;
    cout << bst.aveCompares() << endl;
    return 0;
}
