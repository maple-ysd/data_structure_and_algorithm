#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <queue>
#include <utility>

template <typename Key, typename Value>
class AVLTree
{
public:
    struct Node
    {
        Key key;
        Value value;
        Node *left = nullptr;
        Node *right = nullptr;
        int height;
        Node(Key k, Value v, int h): key(k), value(v), height(h) {}
    };
private:
    Node *root = nullptr;
public:
    AVLTree() {}
    ~AVLTree()
    {
        if (root)
        {
            std::queue<Node*> que;
            que.push(root);
            while (!que.empty())
            {
                Node *temp = que.front();
                que.pop();
                if (temp->left) que.push(temp->left);
                if (temp->right) que.push(temp->right);
                delete temp;
            }
        }
    }
    bool empty()
    {
        return root == nullptr;
    }
    int size()
    {
        int n = 0;
        size(root, n);
        return n;
    }
    void size(Node *proot, int &n)
    {
        if (!root) return;

        size(proot->left, n);
        n += 1;
        size(proot->right, n);
    }
    int getHeight()
    {
        return getHeight(root);
    }
    int getHeight(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    // 插入
    void insert(Key k, Value v)
    {
        root = insert(root, k, v);
    }
    Node *insert(Node *proot, Key k, Value v)
    {
        if (proot == nullptr) return new Node(k, v, 1);

        if (k < proot->key)
        {
            proot->left = insert(proot->left, k, v);
        }
        else if (k > proot->key)
        {
            proot->right = insert(proot->right, k, v);
        }
        else
            proot->value = v;
        proot->height = 1 + std::max(getHeight(proot->left),getHeight(proot->right));
        return balance(proot);
    }
    Node *find(Key k)
    {
        return find(root, k);
    }
    Node *find(Node *node, Key k)
    {
        if (node == nullptr) return nullptr;

        if (k < node->key) return find(node->left, k);
        else if (k > node->key) return find(node->right, k);
        else return node;
    }
    Node *Min()
    {
        return Min(root);
    }
    Node *Min(Node *node)
    {
        if (node == nullptr) return nullptr;

        while (node->left)
            node = node->left;
        return node;
    }
    Node *Max()
    {
        return Max(root);
    }
    Node *Max(Node *node)
    {
        if (node== nullptr) return nullptr;

        while (node->right)
            node = node->right;
        return node;
    }

    void deleteMin()
    {
        if (empty()) return;
        root = deleteMin(root);
    }
    Node *deleteMin(Node *node)
    {

        if (node->left == nullptr)
        {
            Node *temp = node->right;
            delete node;
            return temp;
        }
        node->left = deleteMin(node->left);
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }
    void deleteMax()
    {
        if (empty()) return;

        root = deleteMax(root);
    }
    Node *deleteMax(Node *node)
    {
        if (node->right == nullptr)
        {
            Node *temp = node->left;
            delete node;
            return temp;
        }

        node->right = deleteMax(node->right);
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }

    void remove(Key k)
    {
        if (empty()) return;

        root = remove(root, k);
    }
    Node *remove(Node *node, Key k)
    {
        if (node == nullptr) return nullptr;

        if (k < node->key)
            node->left = remove(node->left, k);
        else if (k > node->key)
            node->right = remove(node->right, k);
        else
        {
            Node *temp = nullptr;
            if (node->left != nullptr && node->right != nullptr)
            {
                temp = Min(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = deleteMin(node->right);
            }
            else
            {
                if (node->left == nullptr)
                    temp = node->right;
                else
                    temp = node->left;
                delete node;
                return temp;
            }
        }
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }

    // 遍历 以查看结果
    void preOrderTraversal()
    {
        preOrderTraversal(root);
    }
    void preOrderTraversal(Node *node)
    {
        if  (node == nullptr) return;

        std::cout << node->key << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
    void inOrderTraversal()
    {
        inOrderTraversal(root);
    }
    void inOrderTraversal(Node *node)
    {
        if  (node == nullptr) return;

        inOrderTraversal(node->left);
        std::cout << node->key << " ";
        inOrderTraversal(node->right);
    }
    void postOrderTraversal()
    {
        postOrderTraversal(root);
    }
    void postOrderTraversal(Node *node)
    {
        if  (node == nullptr) return;

        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << node->key << " ";
    }

private:
    Node *rotateLeft(Node *node)
    {
        if (node == nullptr || node->right == nullptr)
            return node;

        Node *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }
    Node *rotateRight(Node *node)
    {
        if (node == nullptr || node->left == nullptr)
            return node;
        Node *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }
    // 平衡因子： 左右子树高差为-1、0、1
    int balanceFactor(Node *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node *balance(Node *node)
    {
        if (balanceFactor(node) < -1)
        {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        if (balanceFactor(node) > 1)
        {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
        return node;
    }
};


#endif // AVLTREE_H_
