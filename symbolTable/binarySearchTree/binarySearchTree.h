#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
//template <typename Key, typename Value>
//struct Node
//{
//    Key key;
//    Value value;
//    Node *left;
//    Node *right;
//    int Size;       // 代表以该节点为根节点的子树节点个数
//    Node(Key k, Value v, int sz): key(k), value(v), Size(sz) {}
//};

template <typename Key, typename Value>
class binarySearchTree
{
public:
    struct Node
    {
        Key key;
        Value value;
        Node *left = nullptr;
        Node *right = nullptr;
        int Size;       // 代表以该节点为根节点的子树节点个数
        Node(Key k, Value v, int sz): key(k), value(v), Size(sz) {}
    };
    binarySearchTree(): root(nullptr) {}
    ~binarySearchTree();
    int size() { return size(root); }
    bool empty() { return size() == 0; }
    Node *find(Key k) { return find(root, k); }
    void insert(Key k, Value v) { root = insert(root, k, v); }
    Node *Min()
    {
        if (root == nullptr) return nullptr;
        return Min(root);
    }
    Node *Max()
    {
        if (root == nullptr) return nullptr;
        return Max(root);
    }
    // 返回第一个键不小于k的节点
    Node *lowerBound(Key k)
    {
        return lowerBound(root, k);
    }
    // 返回第一个键大于k的节点
    Node *upperBound(Key k)
    {
        return upperBound(root, k);
    }
    Node *select(int index)
    {
        if (index < 0 && index >= size(root))
            throw std::out_of_range("index can not be negative and must be lower than tree size.\n");
        // 现在第i个节点一定在这个树上且这个树一定非空
        return select (root, index);
    }
    int rank(Key k)
    {
        return rank(root, k);
    }
    void deleteMin()
    {
        if (root == nullptr) return;
        root = deleteMin(root);
    }
    void deleteMax()
    {
        if (root == nullptr) return;
        root = deleteMax(root);
    }
    void Delete(Key k)
    {
        root = Delete(root, k);

    }
    void traversal()
    {
        vec.clear();
        traversal(root, vec);
    }
    void traversal(Node *proot, std::vector<Node*> &v)
    {
        if (proot == nullptr) return;
        traversal(proot->left, v);
        v.push_back(proot);
        traversal(proot->right, v);
    }
//    std::vector<Node*> traversal()
//    {
//        std::vector<Node*> q;
//        if (root == nullptr) return q;
//
//        Key lo, hi;
//        lo = Min()->key;
//        hi = Max()->key;
//        traversal(root, q, lo, hi);
//        return q;
//    }
//    void traversal(Node *proot, std::vector<Node*> &q, Key lo, Key hi)
//    {
//        if (proot == nullptr) return;
//        if (lo < proot->key) traversal(proot->left, q, lo, hi);
//        if (lo <= proot->key && hi >= proot->key) { q.push_back(proot); }
//        if (hi > proot->key) traversal(proot->right, q, lo, hi);
//    }
    typename std::vector<Node*>::iterator begin()
    {
//        vec = traversal();
        traversal();
        return vec.begin();
    }
    typename std::vector<Node*>::iterator end() { return vec.end(); }
    // 计算树高
    int treeHeight()
    {
        return treeHeight(root);
    }
    // 平均随机比较次数：每个节点的高度之和的平均值
    double aveCompares()
    {
        return 1.0 * aveCompares(root, 1) / root->Size;
    }
//    double aveCompares()
//    {
//        if (root == nullptr) return 0;
//        return 1.0 * aveCompares(root) / root->Size;
//    }
private:
    Node *root;
    std::vector<Node*> vec;

    int size(Node *node)
    {
        if (node == nullptr) return 0;
        else return node->Size;
    }
    Node *find(Node *proot, Key k)
    {
        if (proot == nullptr) return nullptr;

        if (k < proot->key) { return find(proot->left, k); }
        else if (k > proot->key) { return find(proot->right, k); }
        else return proot;
    }
    Node *insert(Node *proot, Key k, Value v)
    {
        if (proot == nullptr) { return new Node(k, v, 1); }

        if (k < proot->key) proot->left = insert(proot->left, k, v);
        else if (k > proot->key) proot->right = insert(proot->right, k, v);
        else proot->value = v;
        proot->Size = size(proot->left) + size(proot->right) + 1;
        return proot;
    }
    Node *Min(Node *proot)
    {
        if (proot->left == nullptr) return proot;
        return Min(proot->left);
    }
    Node *Max(Node *proot)
    {
        if (proot->right == nullptr) return proot;
        return Max(proot->right);
    }
    Node *lowerBound(Node *proot, Key k)
    {
        if (proot == nullptr) return nullptr;

        if (proot->key == k) return proot;
        else if (proot->key < k) return lowerBound(proot->right, k);
        else
        {
            Node *temp = lowerBound(proot->left, k);
            if (temp == nullptr) return proot;
            else return temp;
        }
    }
    Node *upperBound(Node *proot, Key k)
    {
        if (proot == nullptr) return nullptr;
        if (proot->key <= k) return upperBound(proot->right, k);
        else
        {
            Node *temp = upperBound(proot->left, k);
            if (temp == nullptr) return proot;
            else return temp;
        }
    }
    Node *select(Node *proot, int index)
    {
        int leftSize = size(proot->left);
        if (leftSize == index) return proot;
        else if (leftSize > index) return select(proot->left, index);
        else return select(proot->right, index - leftSize - 1);
    }
    int rank(Node *proot, Key k)
    {
        if (proot == nullptr) return 0;

        if (k < proot->key) return rank(proot->left, k);
        else if (k > proot->key) return size(proot->left) + 1 + rank(proot->right, k);
        else return size(proot->left);
    }
    Node *deleteMin(Node *proot)
    {
        if (proot->left == nullptr)
        {
            Node *temp = proot->right;
            delete proot;
            return temp;
        }
        proot->left = deleteMin(proot->left);
        proot->Size = size(proot->left) + 1 + size(proot->right);
        return proot;
    }
    Node *deleteMax(Node *proot)
    {
        if (proot->right == nullptr)
        {
            Node *temp = proot->left;
            delete proot;
            return temp;
        }
        proot->right = deleteMax(proot->right);
        proot->Size = size(proot->left) + 1 + size(proot->right);
        return proot;
    }
    Node *Delete(Node *proot, Key k)
    {
        if (proot == nullptr) return nullptr;

        if (k < proot->key) proot->left = Delete(proot->left, k);
        else if (k > proot->key) proot->right = Delete(proot->right, k);
        else
        {
            if (proot->left && proot->right)
            {
                Node *temp = Min(proot->right);
                proot->value = temp->value;
                proot->right = deleteMin(proot->right);
            }
            else
            {
                Node *temp = proot;
                if (!proot->left) proot = proot->right;
                else if (!proot->right) proot = proot->left;
                delete temp;
            }
        }
        if (proot)
            proot->Size = size(proot->left) + 1 + size(proot->right);
        return proot;
    }
    int treeHeight(Node *proot)
    {
        if (proot == nullptr) return 0;
        return std::max(treeHeight(proot->left), treeHeight(proot->right)) + 1;
    }
//    int aveCompares(Node *proot)
//    {
//        if (proot == nullptr) return 0;
//        return aveCompares(proot->left) + aveCompares(proot->right) + proot->Size;
//    }
    int aveCompares(Node *proot, int numberOfCompares)
    {
        if (proot == nullptr) return 0;
        int leftLength = aveCompares(proot->left, numberOfCompares + 1);
        int rightLength = aveCompares(proot->right, numberOfCompares + 1);
        return leftLength + rightLength + numberOfCompares;
    }
};

template <typename Key, typename Value>
binarySearchTree<Key, Value>::~binarySearchTree()
{

    std::queue<Node*> q;
    if (root)
    {
        q.push(root);
        while (!q.empty())
        {
            Node *temp = q.front();
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
            q.pop();
        }
    }
}

#endif // BINARYSEARCHTREE_H_
