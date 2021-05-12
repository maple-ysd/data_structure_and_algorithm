#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

/***************************************************
red black tree
��������ʣ�
1��ÿ�������Ǻ�ɫ�ģ����Ǻ�ɫ��
2�����ڵ��Ǻ�ɫ��
3��ÿ��Ҷ��㣨NIL���Ǻ�ɫ�ģ�Ĭ�Ͽ�����Ϊ��ɫ��
4�����һ���ڵ��Ǻ�ɫ�ģ��������������Ӷ��Ǻ�ɫ�ġ�
5������ÿ����㣬�Ӹý�㵽��Ҷ�ӽ�������·���ϰ�����ͬ��Ŀ�ĺ�ɫ��㡣

�����ʵ�ֲ������������������㷨���İ棩������ǰ��Ļ����ϼ���һ������
���еģ��ȶ�����ڵ�ֻ�ܳ�����������
��˸ö�������ʵ�ֻ���2-3������֮��Եľ���������ʵ��������2-3-4����
****************************************************/

#include <iostream>
#include <string>
#include <queue>    // ���ڲ���������������
template <typename Key, typename Value>
class redBlackTree
{
public:
    static const bool RED = true;
    static const bool BLACK = false;
    struct Node
    {
        Key key;
        Value value;
        Node *left = nullptr;
        Node *right = nullptr;
        int Size;       // ��Ҫ����rank��select,�����Ըýڵ�Ϊ���ڵ�������Ľڵ���
        bool color;
        Node(Key k, Value v, int sz, bool c): key(k), value(v), Size(sz), color(c) {}
    };
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
    void preOrderTraversal()
    {
        preOrderTraversal(root);
    }
    void preOrderTraversal(Node *proot)
    {
        if (proot)
        {
            if (proot->color) std::cout << "R";
            else std::cout << "B";
            std::cout << proot->key << " ";
            preOrderTraversal(proot->left);
            preOrderTraversal(proot->right);
        }
    }

    void inOrderTraversal()
    {
        inOrderTraversal(root);
    }
    void inOrderTraversal(Node *proot)
    {
        if (proot)
        {
            inOrderTraversal(proot->left);
            if (proot->color) std::cout << "R";
            else std::cout << "B";
            std::cout << proot->key << " ";
            inOrderTraversal(proot->right);
        }
    }
    void postOrderTraversal()
    {
        postOrderTraversal(root);
    }
    void postOrderTraversal(Node *proot)
    {
        if (proot)
        {
            postOrderTraversal(proot->left);
            postOrderTraversal(proot->right);
            if (proot->color) std::cout << "R";
            else std::cout << "B";
            std::cout << proot->key << " ";
        }
    }
    int size() { return size(root); }
    int size(Node *node)
    {
        if (node == nullptr) return 0;
        return node->Size;
    }

    bool empty() { return size() == 0; }

    bool isRed(Node *node)
    {
        if (node == nullptr) return false;
        return node->color == RED;
    }

    Node *find(Key k) { return find(root, k); }
    Node *find(Node *proot, Key k)
    {
        if (!proot) return nullptr;
        if (k < proot->key) return find(proot->left, k);
        else if (k > proot->key) return find(proot->right, k);
        else return proot;
    }

    /** ����
     *  ��Ϊ�գ�ֱ�Ӵ���һ���ڵ㣬��rootָ��������
     *  �����գ���R��ʾ��ɫ��B���ʾ��ɫ��X��ʾ������ڵ㣬���Ϻ��£� -��ʾһ��2-3���ڵ�����������
     *  >> ����2�ڵ���
     *                 B3       B3
     *   �����       /          \
     *              XR1          XR5
     *
     *   2-3��    XR1-B3       B3-XR5
     *   ���������ֱ�Ӳ��뼴�ɣ����账��
     *
     *
     *   >> ����3�ڵ���
     *                (1)            (2)               (3)             (���)
     *                 B5             B5
     *   �����       /               /
     *               R3    --->     R3      --->        B3      --->     R3
     *                \             /                  /  \             /  \
     *                XR4          XR1               XR1  R5          XB1  B5
     *
     *   ���������ڵ��Ϲ��������������1����2����3��
     *   �����3��ֱ�ӱ�ɫ����
     *   �����2��ת��Ϊ�����3����ɫ����
     *   �����1���ȱ�Ϊ�����2���ٱ�Ϊ�����3����ɫ����
     *
     *   ��ɫ�����Ժ��ڵ����ƣ����ϲ��иýڵ�λ�������ڲ�����һ����ڵ㣬�����ظ��ù���
     */

    void insert(Key k, Value v)
    {
        root = insert(root, k, v);
        root->color = BLACK;
    }
    Node *insert(Node *proot, Key k, Value v)
    {
        if (proot == nullptr) return new Node(k, v, 1, RED);

        if (k < proot->key)
        {
            proot->left = insert(proot->left, k, v);
        }
        else if (k > proot->key)
        {
            proot->right = insert(proot->right, k, v);
        }
        else proot->value = v;

        if (isRed(proot->right) && !isRed(proot->left))  proot = rotateLeft(proot);
        if (isRed(proot->left) && isRed(proot->left->left)) proot = rotateRight(proot);
        if (isRed(proot->left) && isRed(proot->right)) flipColors(proot);       // �˴���ɫ��ת�Ѻ�ɫ�ڵ����ƣ������ڲ���ڵ�Ϊ�����Ǹ��ڵ㣬Ȼ��ݹ�����
        proot->Size = size(proot->left) + 1 + size(proot->right);
        return proot;
    }

    Node *Min()
    {
        return Min(root);
    }
    Node *Min(Node *node)
    {
        if (!node) return nullptr;

        if (node->left == nullptr) return node;
        return Min(node->left);

//        // ���߲��÷ǵݹ���ʽʵ��
//        while (node->left)
//            node = node->left;
//        return node;
    }
    Node *Max()
    {
        return Max(root);
    }
    Node *Max(Node *node)
    {
        if (node == nullptr) return nullptr;

        while (node->right)
            node = node->right;
        return node;
    }

    Node *lowerBound(Key k)
    {
        return lowerBound(root, k);
    }
    Node *lowerBound(Node *node, Key k)     // �ҵ�һ����С��k�Ľڵ�
    {
        if (node == nullptr) return nullptr;

        if (k < node->key)
        {
            Node *temp = lowerBound(node->left, k);
            if (temp != nullptr)
                return temp;
            else
                return node;
        }
        else if (k > node->key) return (lowerBound(node->right, k));
        else return node;
    }

    Node *upperBound(Key k)
    {
        return upperBound(root, k);
    }
    Node *upperBound(Node *node, Key k)     // �ҵ�һ������k�Ľڵ�
    {
        if (node == nullptr) return nullptr;

        if (k < node->key) return upperBound(node->right, k);
        else if (k > node->key)
        {
            Node *temp = upperBound(node->left, k);
            if (temp != nullptr)
                return temp;
            else
                return node;
        }
    }

    Node *select(int index)
    {
        if (index >= size())
            throw std::out_of_range("index out of range in select operation.\n");

        return select(root, index);
    }
    Node *select(Node *node, int index)
    {
        int leftSubTreeSize = size(node->left);
        if (index < leftSubTreeSize) return select(node->left, index);
        else if (index > leftSubTreeSize) return select(node->right, index - leftSubTreeSize - 1);
        else return node;
    }

    int rank(Key k)     // ��ʾС�ڸü�ֵ�Ľڵ����
    {
        return rank(root, k);
    }
    int rank(Node *node, Key k)
    {
        if (node == nullptr) return 0;

        if (k < node->key) return rank(node->left, k);
        else if (k > node->key) return size(node->left) + 1 + rank(node->right, k);
        else return size(node->left);
    }
    /** ɾ����С�ڵ�
     *  ����ɾ���ڵ�һ��Ϊ��ɫ��
     *  ��Ϊ�գ����账��
     *  �����գ����������´���֮ǰ��ȷ����ǰ�ڵ������һ��Ϊ��ڵ��ǰ�ڵ�����ӵ�����һ��Ϊ��ڵ㣩
     *
     *  �Զ����²��ҹ����У�����֤ÿһ���ڵ��Ƿ�Ϊ��С�ڵ�֮ǰ����������Ҫ�����ֵ� "��"��ȷ�����ܶ�Ӧ2-3����һ��3�ڵ������ʱ4�ڵ㣬
     * ����������е�ǰ�ڵ�������ӽڵ�Ϊ��ڵ㣩��Ȼ��ɾ���ýڵ㣬��Ӱ��2-3����ƽ�⣬Ȼ���Ե����ϣ���ƽ
     *
     *  >>>> ��������������������������²�ѯ
     *             (1)         (2)
     *             B5          B5
     *            /           /  \
     *  �����   XR1         B3  B7                    ��ǰ�ڵ������Ϊ��ڵ� �� ��ǰ�ڵ�����ӵ�����Ϊ��ڵ�
     *                      /
     *                    XR1
     *
     *  2-3��  XR1-B5        B5                          ������ﵱǰ�ڵ������
     *                      /  \               ��Ӧ�ģ���ǰ�ڵ�Ϊ3�ڵ�ʱ����3�ڵ�����
     *                  XR1-B3 B7                      ��ǰ�ڵ㲻Ϊ3�ڵ㵫��ǰ�ڵ������Ϊ3�ڵ㣬��3�ڵ���Ҽ�
     *
     *  >>>> ���������������Ҫ�����ֵܽڵ㡰�衱һ��
     *      (1)
     *          R5              B5             B5             B6               R6               �����
     *         /  \            /  \           /  \           /  \             /  \
     *        B3  B7   --->   R3  R7  --->   R3  R6    ---> R5  R7    --->   B5  B7
     *            /               /                \       /                /
     *           R6              R6                R7     R3               R3
     *
     *         R5                                                               R6              2-3��
     *        /  \            ------------------------------------>            /  \
     *       B3 R6-B7                                                       R3-B5 B7            ���衱���
     *
     *       (2)
     *          R5              B5         �����
     *         /  \   --->     /  \
     *        B3  B7          R3  R7
     *
     *          R5
     *         /  \   --->   R3-B5-R7       2-3��        �費�ˣ��ͺϳ���ʱ4�ڵ�������
     *        B3  B7
     */

    void deleteMin()
    {
        if (root == nullptr) return;

        if (!isRed(root->left && !isRed(root->right)))      // ȷ�����ڵ����ڵ������Ϊ��ɫ
            root->color = RED;

        root = deleteMin(root);

        if (!empty())
            root->color = BLACK;
    }
    /** ���ýڵ�Ϊ��С�ڵ㣬������Ϊ�գ�ֱ��ɾ��
     *  ��֮��
     *      �ж������Ƿ�Ϊ�ڶ��ڵ㣬���ǣ����������Һ��ӽ裬����Ϊ�ڵ�����£��Һ���һ�����ڣ�
     *      ���������������ϼ����ݹ飨���£�ɾ����С�ڵ�
     *      ���ǵã��������ϣ�ƽ��
     */

    Node *deleteMin(Node *node)
    {
        if (node->left == nullptr)
        {
            delete node;
            return nullptr;
        }

        if (!isRed(node->left) && !isRed(node->left->left))         // �ж�������Ϊ��2�ڵ㣬 �������ֵܡ��衱һ��
        {
            node = moveRedLeft(node);
        }

        node->left = deleteMin(node->left);

        return balance(node);
    }

    /**< ��ɾ����С�ڵ㲻ͬ��һ�������ڵ�Ϊ�ڽڵ㣬�����Ҫ����һ�������ڵ�Ϊ��ɫ�������������� */
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
        if (isRed(node->left))
            node = rotateRight(node);

        if (node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        if (!isRed(node->right) && !isRed(node->right->left))   // �ж��Ƿ�Ϊ�ڶ��ڵ�
        {
            node = moveRedRight(node);
        }

        node->right = deleteMax(node->right);
        return balance(node);
    }

    void remove(Key k)
    {
        if (find(k) == nullptr) return;

        if (!isRed(root->left) && !isRed(root->right))
            root->color = RED;

        root = remove(root, k);

        if (!empty())
            root->color = BLACK;
    }

    /**<
    ��k < node->key, ������ߣ�����֮ǰɾ����С����������ƵĴ���һ�£�ȷ����ǰ�ڵ������Ϊ��ڵ㣬���ߵ�ǰ�ڵ�����ӵ�����Ϊ��ڵ�
    ��k > node->key, ���ұ��ߣ�����֮ǰɾ��������������ƵĴ���һ�£�ȷ����ǰ�ڵ���Һ���Ϊ��ڵ㣬 ��ǰ�ڵ���Һ��ӵ��Һ���Ϊ��ڵ�
    ��k == node->key, �����Ϊ��ڵ�������һ�£� Ȼ���ж��Һ����Ƿ�Ϊ�գ��ǵĻ�ɾ������������һ����Ϊ�˱���ɾ���ýڵ������ʧȥ�����ӣ�
                                                �����м�ڵ㣬���Ȱ����� > �������ȷ���Һ���Ϊ��ڵ���Һ��ӵ��Һ���Ϊ��ڵ㣬
                                                Ȼ����Min(node->right)����ǰ�ڵ㣬ɾ��node->right ����С�ڵ�
     */
    Node *remove(Node *node, Key k)
    {
        if (node == nullptr) return nullptr;

        if (k < node->key)
        {
            if (!isRed(node->left) && node->left != nullptr && !isRed(node->left->left))
                node = moveRedLeft(node);
            node->left = remove(node->left, k);
        }
        else
        {
            if (isRed(node->left)) node = rotateRight(node);    // ȷ�����ڵ㲻��Ͽ�������ȷ���Ҳ�ڵ�Ϊ��ڵ��ýڵ�ĺ���Ϊ��ڵ�

            if (k == node->key && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            if (!isRed(node->right) && node->right != nullptr && !isRed(node->right->left))
                node = moveRedRight(node);

            if (k == node->key)
            {
                Node *aux = Min(node->right);
                node->key = aux->key;
                node->value = aux->value;
                node->right = deleteMin(node->right);
            }
            else
                node->right = remove(node->right, k);
        }
        return balance(node);
    }
private:
    Node *root = nullptr;

    Node *rotateLeft(Node *node)
    {
        // �����Ѽ���ýڵ���Һ���Ϊ��ڵ�
        // std::assert(node != nullptr && isRed(node->right));
        if (node == nullptr || !isRed(node->right)) return nullptr;

        Node *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        newRoot->Size = node->Size;
        node->Size = size(node->left) + 1 + size(node->right);

        newRoot->color = node->color;
        node->color = RED;          // �����Ѽ���ýڵ���Һ���Ϊ��ڵ㣬�ü�������������

        return newRoot;
    }
    Node *rotateRight(Node *node)
    {
        // �������ýڵ������Ϊ��ڵ�
        // std::assert(node != nullptr && isRed(node->left));
        if (node == nullptr || !isRed(node->left)) return nullptr;

        Node *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        newRoot->Size = node->Size;
        node->Size = size(node->left) + 1 + size(node->right);

        newRoot->color = node->color;
        node->color = RED;      // �����Ѽ���ýڵ���Һ���Ϊ��ڵ㣬�ü�������������

        return newRoot;
    }
    void flipColors(Node *node)
    {
        // ��֤�ýڵ����������ӽڵ�һ������
        if (!node || !node->left || !node->right) return;

        // �ýڵ����������ӽڵ�����෴����ɫ
        if ((isRed(node) && !isRed(node->left) && !isRed(node->right)) || (!isRed(node) && isRed(node->left) && isRed(node->right)))
        {
            node->color = !node->color;
            node->left->color = !node->left->color;
            node->right->color = !node->right->color;
        }
    }

    // ��ǰ�ڵ������Ϊ��2�ڵ㣬���Һ��ӽ�һ��
    Node *moveRedLeft(Node *node)
    {
        // ����node�ڵ�Ϊ��ɫ���������ӣ��Լ����ӵ����Ӿ�Ϊ��ɫ
        // �뷽�跨ʹ�����ӱ�죬�������ӵ����ӱ��
        flipColors(node);

        if (node->right != nullptr && isRed(node->right->left))
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    // ��ǰ�ڵ���Һ���Ϊ��2�ڵ㣬�����ӽ�һ��
    Node *moveRedRight(Node *node)
    {
        // ������û�ý�
        flipColors(node);
        // �����еĽ�
        if  (node->left != nullptr && isRed(node->left->left))
        {
            node = rotateRight(node);
            flipColors(node);
        }
        return node;
    }

    Node *balance(Node *node)
    {
        if (node == nullptr) return nullptr;

        if (isRed(node->right) && !isRed(node->left))
            node = rotateLeft(node);
        if (isRed(node->left) && isRed(node->left->left))
            node = rotateRight(node);
        if (isRed(node->left) && isRed(node->right))
            flipColors(node);

        node->Size = size(node->left) + 1 + size(node->right);
        return node;
    }
};

#endif // REDBLACKTREE_H_
