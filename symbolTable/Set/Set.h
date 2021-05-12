#ifndef SET_H_
#define SET_H_

/**Set 的实现基于红黑树
 *（这里采用基于2-3树的左倾红黑树）
 */

#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

template <typename Key>
class Set
{
    class redBlackTree
    {
        enum { RED = true, BLACK = false };
        struct Node
        {
            Key key;
            Node *left = nullptr;
            Node *right = nullptr;
            bool color = RED;
            int Size;
            Node(Key k, int sz): key(k), left(nullptr), right(nullptr), color(RED), Size(sz) {}
        };
    public:
        redBlackTree(): root(nullptr) {}
        ~redBlackTree()
        {
            if (root)
            {
                std::queue<Node*> que;
                que.push(root);
                Node *temp = nullptr;
                while (!que.empty())
                {
                    temp = que.front();
                    que.pop();
                    if (temp->left) que.push(temp->left);
                    if (temp->right) que.push(temp->right);
                    delete temp;
                }
            }
        }
    private:
        Node *root = nullptr;
    public:
        bool empty() { return root == nullptr; }
        int size()
        {
            return size(root);
        }
        bool contains(Key k)
        {
            if (empty()) return false;

            Node *node = root;
            while (node)
            {
                if (k < node->key) node = node->left;
                else if (k > node->key) node = node->right;
                else return true;
            }
            return false;
        }
        void insert(Key k)
        {
            root = insert(root, k);
            root->color = BLACK;
        }
        Node *insert(Node *node, Key k)
        {
            if (node == nullptr) return new Node(k, 1);

            if (k < node->key) node->left = insert(node->left, k);
            else if (k > node->key) node->right = insert(node->right, k);
            else return node;
            return balance(node);
        }
        void deleteMin()
        {
            if (empty()) return;

            if (!isRed(root->left) && !isRed(root->right))
                root->color = RED;

            root = deleteMin(root);

            if (!empty())
                root->color = BLACK;
        }
        Node *deleteMin(Node *node)
        {
            if (node->left == nullptr)
            {
                delete node;
                return nullptr;
            }

            if (!isRed(node->left) && !isRed(node->left->left))
                node = moveRedLeft(node);

            node->left = deleteMin(node->left);

            return balance(node);
        }
        void deleteMax()
        {
            if (empty()) return;

            if (!isRed(root->left) && !isRed(root->right))
                root->color = RED;

            root = deleteMax(root);

            if (!empty())
                root->color = BLACK;
        }
        Node *deleteMax(Node *node)
        {
            if (isRed(node->left)) node = rotateRight(node);

            if (node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            if (!isRed(node->right) && !isRed(node->right->left))
                node = moveRedRight(node);

            node->right = deleteMax(node->right);
            return balance(node);
        }

        Node *Min()
        {
            if (empty()) return nullptr;
            return Min(root);
        }
        Node *Max()
        {
            if (empty()) return nullptr;
            return Max(root);
        }
        void remove(Key k)
        {
            if (empty() || !contains(k)) return;

            if (!isRed(root->left) && !isRed(root->right))
                root->color = RED;

            root = remove(root, k);

            if (!empty())
                root->color = BLACK;
        }
        Node *remove(Node *node, Key k)
        {
            if (k < node->key)
            {
                if (!isRed(node->left) && !isRed(node->left->left))
                    node = moveRedLeft(node);
                node->left = remove(node->left, k);
            }
            else
            {
                if (isRed(node->left)) node = rotateRight(node);

                if (node->right == nullptr && node->key == k)
                {
                    delete node;
                    return nullptr;
                }
                if (!isRed(node->right) && node->right != nullptr && !isRed(node->right->left))
                    node = moveRedRight(node);

                if (node->key == k)
                {
                    Node *temp = Min(node->right);
                    node->key = temp->key;
                    node->right = deleteMin(node->right);
                }
                else
                    node->right = remove(node->right, k);
            }
            return balance(node);
        }

        Node *select(int i)
        {
            if (i < 0 || i >= size())
                throw std::invalid_argument("no such element");
            return select(root, i);
        }
        Node *select(Node *node, int i)
        {
            if (i < size(node->left)) return select(node->left, i);
            else if (i > size(node->left)) return select(node->right, i - size(node->left) - 1);
            else return node;
        }
        int rank(Key k)
        {
            return rank(root, k);
        }
        int rank(Node *node, Key k)
        {
            if (node == nullptr) return 0;
            if (k < node->key) return rank(node->left, k);
            else if( k > node->key) return size(node->left) + 1 + rank(node->right, k);
            else return size(node->left);
        }
        std::vector<Key> keys()
        {
            std::vector<Key> v;
            keys(root, v);
            return v;
        }
        void keys(Node *node, std::vector<Key> &v)
        {
            if (node == nullptr) return;

            keys(node->left, v);
            v.push_back(node->key);
            keys(node->right, v);
        }
    private:
        int size(Node *node)
        {
            if (node == nullptr) return 0;
            return node->Size;
        }
        bool isRed(Node *node)
        {
            if (node == nullptr) return false;
            else return node->color == RED;
        }
        Node *rotateLeft(Node *node)
        {
            if (node == nullptr || node->right == nullptr || !isRed(node->right))
                return node;
            Node *newRoot = node->right;
            node->right = newRoot->left;
            newRoot->left = node;

            newRoot->color = node->color;
            node->color = RED;

            newRoot->Size = node->Size;
            node->Size = size(node->left) + 1 + size(node->right);
            return newRoot;
        }
        Node *rotateRight(Node *node)
        {
            if (node == nullptr || node->left == nullptr || !isRed(node->left))
                return node;

            Node *newRoot = node->left;
            node->left = newRoot->right;
            newRoot->right = node;

            newRoot->color = node->color;
            node->color = RED;

            newRoot->Size = node->Size;
            node->Size = size(node->left) + size(node->right) + 1;
            return newRoot;
        }
        void flipColors(Node *node)
        {
            if (node == nullptr || node->left == nullptr || node->right == nullptr)
                return;

            if ((isRed(node) && !isRed(node->left) && !isRed(node->right))
                || (!isRed(node) && isRed(node->left) && isRed(node->right)))
            {
                node->color = !node->color;
                node->left->color = !node->left->color;
                node->right->color = !node->right->color;
            }
        }

        Node *moveRedLeft(Node *node)
        {
            // 这里假设node为红，node->left 和 node->left->left 均为黑
            // 该操作使node->left 或node->left的左孩子变为红色

            flipColors(node);
            if (node->right != nullptr && isRed(node->right->left))
            {
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
                flipColors(node);
            }
            return node;
        }
        Node *moveRedRight(Node *node)
        {
            // 这里假设node为红，node->right 和 node->right->left 均为黑
            // 该操作使node->right 或node->right的右孩子变为红色

            flipColors(node);
            if (node->left != nullptr && isRed(node->left->left))
            {
                node = rotateRight(node);
                flipColors(node);
            }
            return node;
        }
        Node *balance(Node *node)
        {
            if (node == nullptr) return node;
            if (isRed(node->right) && !isRed(node->left)) node = rotateLeft(node);
            if (isRed(node->left) && isRed(node->left->left)) node = rotateRight(node);
            if (isRed(node->left) && isRed(node->right)) flipColors(node);

            node->Size = size(node->left) + 1 + size(node->right);
            return node;
        }
        Node *Min(Node *node)
        {
            if (node->left == nullptr)
                return node;
            return Min(node->left);
        }
        Node *Max(Node *node)
        {
            if (node->right == nullptr) return node;
            return Max(node->right);
        }

    };

public:
    Set() {}
    ~Set() {}
private:
    redBlackTree rbt;
public:
    bool empty() { return rbt.empty(); }
    int size() { return rbt.size(); }
    bool contains(Key k) { return rbt.contains(k); }
    int rank(Key k) { return rbt.rank(k); }
    Key select(int i)
    {
        if (i >= size() || i < 0)
            throw std::invalid_argument("no such element.\n");
        return rbt.select(i)->key;
    }
    void add(Key k)
    {
        rbt.insert(k);
    }
    void remove(Key k)
    {
        rbt.remove(k);
    }
    Key Min()
    {
        if (empty())
            throw std::runtime_error("empty set, Min operation failed.\n");
        return rbt.Min()->key;
    }
    Key Max()
    {
        if (empty())
            throw std::runtime_error("empty set, Max operation failed.\n");
        return rbt.Max()->key;
    }
    void deleteMin()
    {
        rbt.deleteMin();
    }
    void deleteMax()
    {
        rbt.deleteMax();
    }
    std::vector<Key> keys()
    {
        return rbt.keys();
    }
};

#endif // SET_H_
