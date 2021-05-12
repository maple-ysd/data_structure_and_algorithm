#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

/***************************************************
red black tree
红黑树性质：
1、每个结点或是红色的，或是黑色的
2、根节点是黑色的
3、每个叶结点（NIL）是黑色的（默认空链接为黑色）
4、如果一个节点是红色的，则它的两个儿子都是黑色的。
5、对于每个结点，从该结点到其叶子结点的所有路径上包含相同数目的黑色结点。

这里的实现采用左倾红黑树（参照算法第四版），即在前面的基础上加上一条限制
所有的（稳定）红节点只能出现在左孩子上
因此该二三树的实现基于2-3树（与之相对的经典红黑树的实现依赖于2-3-4树）
****************************************************/

#include <iostream>
#include <string>
#include <queue>    // 用于层序遍历析构红黑树
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
        int Size;       // 主要用于rank和select,代表以该节点为根节点的子树的节点数
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

    /** 插入
     *  树为空：直接创建一个节点，让root指向它即可
     *  树不空：（R表示红色，B表和示黑色，X表示待插入节点，黑上红下， -表示一个2-3树节点包含多个键）
     *  >> 插在2节点上
     *                 B3       B3
     *   红黑树       /          \
     *              XR1          XR5
     *
     *   2-3树    XR1-B3       B3-XR5
     *   这种情况下直接插入即可，无需处理
     *
     *
     *   >> 插在3节点上
     *                (1)            (2)               (3)             (结果)
     *                 B5             B5
     *   红黑树       /               /
     *               R3    --->     R3      --->        B3      --->     R3
     *                \             /                  /  \             /  \
     *                XR4          XR1               XR1  R5          XB1  B5
     *
     *   插入在三节点上共以上三种情况（1）（2）（3）
     *   情况（3）直接变色即可
     *   情况（2）转化为情况（3）变色处理
     *   情况（1）先变为情况（2）再变为情况（3）变色处理
     *
     *   变色处理以后红节点上移，在上层中该节点位置类似于插入了一个红节点，继续重复该过程
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
        if (isRed(proot->left) && isRed(proot->right)) flipColors(proot);       // 此处颜色翻转把红色节点上移，类似于插入节点为上面那个节点，然后递归向上
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

//        // 或者采用非递归形式实现
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
    Node *lowerBound(Node *node, Key k)     // 找第一个不小于k的节点
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
    Node *upperBound(Node *node, Key k)     // 找第一个大于k的节点
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

    int rank(Key k)     // 表示小于该键值的节点个数
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
    /** 删除最小节点
     *  （被删除节点一定为红色）
     *  树为空，不予处理
     *  树不空：（继续向下传递之前，确保当前节点的左孩子一定为红节点或当前节点的左孩子的左孩子一定为红节点）
     *
     *  自顶向下查找过程中，在验证每一个节点是否为最小节点之前，（可能需要向其兄弟 "借"）确保其能对应2-3树中一个3节点或者临时4节点，
     * （即红黑树中当前节点或其左子节点为红节点）。然后删除该节点，不影响2-3树的平衡，然后自底向上，配平
     *
     *  >>>> 以下两种情况不做处理，继续向下查询
     *             (1)         (2)
     *             B5          B5
     *            /           /  \
     *  红黑树   XR1         B3  B7                    当前节点的左孩子为红节点 或 当前节点的左孩子的左孩子为红节点
     *                      /
     *                    XR1
     *
     *  2-3树  XR1-B5        B5                          红黑树里当前节点的左孩子
     *                      /  \               对应的：当前节点为3节点时，该3节点的左键
     *                  XR1-B3 B7                      当前节点不为3节点但当前节点的左孩子为3节点，该3节点的右键
     *
     *  >>>> 以下两种情况，需要向其兄弟节点“借”一下
     *      (1)
     *          R5              B5             B5             B6               R6               红黑树
     *         /  \            /  \           /  \           /  \             /  \
     *        B3  B7   --->   R3  R7  --->   R3  R6    ---> R5  R7    --->   B5  B7
     *            /               /                \       /                /
     *           R6              R6                R7     R3               R3
     *
     *         R5                                                               R6              2-3树
     *        /  \            ------------------------------------>            /  \
     *       B3 R6-B7                                                       R3-B5 B7            “借”完成
     *
     *       (2)
     *          R5              B5         红黑树
     *         /  \   --->     /  \
     *        B3  B7          R3  R7
     *
     *          R5
     *         /  \   --->   R3-B5-R7       2-3树        借不了，就合成临时4节点来处理
     *        B3  B7
     */

    void deleteMin()
    {
        if (root == nullptr) return;

        if (!isRed(root->left && !isRed(root->right)))      // 确保根节点或根节点的左孩子为红色
            root->color = RED;

        root = deleteMin(root);

        if (!empty())
            root->color = BLACK;
    }
    /** 若该节点为最小节点，即左孩子为空，直接删除
     *  反之：
     *      判断左孩子是否为黑二节点，若是，调整（向右孩子借，左孩子为黑的情况下，右孩子一定存在）
     *      调整后，在其左孩子上继续递归（向下）删除最小节点
     *      最后记得（迭代向上）平衡
     */

    Node *deleteMin(Node *node)
    {
        if (node->left == nullptr)
        {
            delete node;
            return nullptr;
        }

        if (!isRed(node->left) && !isRed(node->left->left))         // 判断若左孩子为黑2节点， 则向其兄弟“借”一下
        {
            node = moveRedLeft(node);
        }

        node->left = deleteMin(node->left);

        return balance(node);
    }

    /**< 与删除最小节点不同的一点是最大节点为黑节点，因此需要右旋一次是最大节点为红色，其他过程类似 */
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

        if (!isRed(node->right) && !isRed(node->right->left))   // 判断是否为黑二节点
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
    若k < node->key, 往左边走，照着之前删除最小的情况，类似的处理一下，确保当前节点的左孩子为红节点，或者当前节点的左孩子的左孩子为红节点
    若k > node->key, 往右边走，照着之前删除最大的情况，类似的处理一下，确保当前节点的右孩子为红节点， 或当前节点的右孩子的右孩子为红节点
    若k == node->key, 若左侧为红节点先右旋一下， 然后判断右孩子是否为空，是的话删除（这里右旋一下是为了避免删除该节点后左孩子失去了链接）
                                                若是中间节点，则先按类似 > 情况处理，确保右孩子为红节点或右孩子的右孩子为红节点，
                                                然后复制Min(node->right)到当前节点，删除node->right 的最小节点
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
            if (isRed(node->left)) node = rotateRight(node);    // 确保左侧节点不会断开，并且确保右侧节点为红节点或该节点的孩子为红节点

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
        // 这里已假设该节点的右孩子为红节点
        // std::assert(node != nullptr && isRed(node->right));
        if (node == nullptr || !isRed(node->right)) return nullptr;

        Node *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;

        newRoot->Size = node->Size;
        node->Size = size(node->left) + 1 + size(node->right);

        newRoot->color = node->color;
        node->color = RED;          // 这里已假设该节点的右孩子为红节点，该假设在这里体现

        return newRoot;
    }
    Node *rotateRight(Node *node)
    {
        // 这里假设该节点的左孩子为红节点
        // std::assert(node != nullptr && isRed(node->left));
        if (node == nullptr || !isRed(node->left)) return nullptr;

        Node *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;

        newRoot->Size = node->Size;
        node->Size = size(node->left) + 1 + size(node->right);

        newRoot->color = node->color;
        node->color = RED;      // 这里已假设该节点的右孩子为红节点，该假设在这里体现

        return newRoot;
    }
    void flipColors(Node *node)
    {
        // 保证该节点与其左右子节点一定存在
        if (!node || !node->left || !node->right) return;

        // 该节点与其两个子节点具有相反的颜色
        if ((isRed(node) && !isRed(node->left) && !isRed(node->right)) || (!isRed(node) && isRed(node->left) && isRed(node->right)))
        {
            node->color = !node->color;
            node->left->color = !node->left->color;
            node->right->color = !node->right->color;
        }
    }

    // 当前节点的左孩子为黑2节点，找右孩子借一下
    Node *moveRedLeft(Node *node)
    {
        // 假设node节点为红色，他的左孩子，以及左孩子的左孩子均为黑色
        // 想方设法使其左孩子变红，或者左孩子的左孩子变红
        flipColors(node);

        if (node->right != nullptr && isRed(node->right->left))
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
            flipColors(node);
        }
        return node;
    }

    // 当前节点的右孩子为黑2节点，找左孩子借一下
    Node *moveRedRight(Node *node)
    {
        // 若左孩子没得借
        flipColors(node);
        // 左孩子有的借
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
