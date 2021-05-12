#ifndef CLASSICALREDBLACKTREE_H_
#define CLASSICALREDBLACKTREE_H_

/**************************************
经典红黑树的实现
1.每个结点要么是红的要么是黑的。

2.根结点是黑的。

3.每个叶结点（叶结点即指树尾端NULL结点）都是黑的。

4.如果一个结点是红的，那么它的两个儿子都是黑的，即不存在两个连续的红节点

5.对于任意结点而言，其到叶结点树尾端NULL指针的每条路径都包含相同数目的黑结点。
***************************************/

#include <queue>

template <typename Key, typename Value>
class classicalRedBlackTree
{
private:
    static const bool RED = true;
    static const bool BLACK = false;
public:
    struct Node
    {
        Key key;
        Value value;
        bool color;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;
        Node(Key k, Value v): key(k), value(v), color(RED) {}
    };
private:
    Node *root = nullptr;
public:
    classicalRedBlackTree() {}
    ~classicalRedBlackTree()
    {
        // 通过层序遍历删除树的各个节点
        if (!root)
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
    // 前序遍历
    void preOrderTraversal(Node *proot)
    {
        if (proot)
        {
            if (proot->color) std::cout << 'R';
            else std::cout << 'B';
            std::cout << proot->key << " ";
            preOrderTraversal(proot->left);
            preOrderTraversal(proot->right);
        }
    }
    void preOrderTraversal()
    {
        preOrderTraversal(root);
    }
    // 中序遍历
    void inOrderTraversal(Node *proot)
    {
        if (proot)
        {
            inOrderTraversal(proot->left);
            if (proot->color) std::cout << 'R';
            else std::cout << 'B';
            std::cout << proot->key << " ";
            inOrderTraversal(proot->right);
        }
    }
    void inOrderTraversal()
    {
        inOrderTraversal(root);
    }
    // 后序遍历
    void postOrderTraversal(Node *proot)
    {
        if (proot)
        {
            postOrderTraversal(proot->left);
            postOrderTraversal(proot->right);
            if (proot->color) std::cout << 'R';
            else std::cout << 'B';
            std::cout << proot->key << " ";
        }
    }
    void postOrderTraversal()
    {
        postOrderTraversal(root);
    }
    /** 左旋：
     *     p                   p
     *     |                   |
     *     x                   y（rx）
     *    / \      ---->      / \
     *   lx  y（rx）         x   ry
     *      / \             / \
     *     ly  ry          lx  ly
     */
    void rotateLeft(Node *x)
    {
        if (x == nullptr || x->right == nullptr) return;

        Node *y = x->right;

        // 先处理节点ly相关, 即节点x的右孩子的左孩子
        x->right = y->left;
        if (y->left) y->left->parent = x;

        // 处理节点y
        y->left = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;   // 说明为根节点，红黑树里面只有根节点没有双亲节点
        }
        else
        {
            if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
        }

        // 最后处理x节点
        x->parent = y;
    }

    /** 右旋：
     *          p                       p
     *          |                       |
     *          y                       x（ly）       该行的x、y节点可能为p的左孩字或右孩子节点，也可能为根节点（如果p为空的话）
     *         / \          ---->      / \
     *  （ly）x   ry                  lx  y
     *       / \                         / \
     *     lx  ly                      ly  ry
     */
    void rotateRight(Node *y)
    {
        if (y == nullptr || y->left == nullptr) return;

        Node *x = y->left;

        // 先处理节点ly相关
        if (x->right) x->right->parent = y;
        y->left = x->right;

        // 处理x节点
        x->right = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
        {
            root = x;   // 说明为根节点,更新根节点
        }
        else
        {
            if (y == y->parent->left) y->parent->left = x;
            else y->parent->right = x;
        }

        // 最后处理y节点
        y->parent = x;
    }

    /** 插入后修复
    *
    * 对于3节点或4节点，稳定状态一定是上黑下红,红黑树里的红节点与其双亲黑节点在二三树里面为一个3节点或者4节点
    *
    * 这里新插入元素表示为X, B表示黑节点， R表示红节点
    *
    * 1.二节点变三节点， 或插在左边或插在右边，直接插入，不需要调整
    *             B2              B2
    *  红黑树     /                \
    *            XR1               XR3
    *
    *  2-3-4树  XR1-B2           B2-XR3
    *
    * 2. 三节点变四节点
    * 2.1            (1)插在爷爷节点的左子树上              (2)插在爷爷节点的右子树上                     （3）
    *             B5                     B5                 B3                      B3                         B5                B5
    *             /                      /                    \                      \                        /  \              /  \
    *            R3  ------>  B3        R3        ......      R5       ......         R5     ......          R3  XR7          XR3  R7
    *           /            /  \        \                      \                     /
    *          XR1          XR1 R5      XR4                     XR7                  XR4
    *                             可通过左旋变为前一种情况                     可通过右旋变为前一种情况    这种情况在红黑树里允许存在，不做调整
    *  2-3-4树    XR1-R3-B5           R3-XR4---B5              B3-R5-XR7           B3---XR4-R5               R3-B5-XR7         XR3-B5-R7
    *
    * 3. 四节点新增：左右子节点变黑双亲节点变红
    * 1）颜色变换
    *           B5              R5         B5              R5                     B5              R5            B5              R5
    *          /  \            /  \       /  \            /  \                   /  \            /  \          /  \            /  \
    *         R3  R7 ------>  B3  B7     R3  R7 ------>  B3  B7                 R3  R7 ------>  B3  B7        R3  R7 ------>  B3  B7
    *        /               /            \               \                           \               \            /              /
    *       R1              R1            R4             R4                           XR9             XR9         XR6            XR6
    * 2）转化为在二节点上插入一个新节点变为三节点的问题，二节点变为3节点当前节点不需要变换， 但产生的红节点可能会导致父节点的调整，递归或迭代向上
    *
    *
    * 总结， 双亲节点为黑，不需要调整，
    * 只有双亲节点为红时才需要调整：（分为两类大情况）
    * >> 双亲结点是爷爷节点的左孩子
    *
    *   >> 叔叔节点为红色，直接变色（爷爷节点，叔叔节点，双亲节点），爷爷节点变红可能会影响上层树的结构，递归或迭代向上处理
    *   >> 叔叔节点为黑色
    *       >> 当前节点为双亲节点的左孩子：交换爷爷节点与双亲节点的颜色，右旋，修复完成
    *       >> 当前节点为双亲节点的右孩子：交换当前节点与双亲节点的颜色，左旋，旋转之后变为上一种情况
    *
    * >> 双亲结点是爷爷节点的右孩子
    *
    *   >> 叔叔节点为红色，直接变色（爷爷节点，叔叔节点，双亲节点），爷爷节点变红可能会影响上层树的结构，递归或迭代向上处理
    *   >> 叔叔节点为黑色
    *       >> 当前节点为双亲节点的右孩子：交换爷爷节点与双亲节点的颜色，左旋，修复完成
    *       >> 当前节点为双亲节点的左孩子：交换当前节点与双亲节点的颜色，右旋，旋转之后变为上一种情况
    *
    * >>>> 注意：当前节点为根节点时，颜色变黑，因为根节点要保持为黑色
    */
    void fixAfterInsert(Node *x)
    {
        while (x != root && x->parent->color == RED)
        {   // x != root等价于x->parent != nullptr 表示双亲节点存在,另外双亲结点为红节点表示爷爷节点一定存在，上黑下红，稳定状态下红节点在二三四树里不能单独存在
            Node *p = x->parent;     // p表示双亲
            Node *g = p->parent;     // g表示爷爷节点
            if (p == g->left)
            {
                Node *u = g->right;     // u表示叔叔节点
                if (u && u->color == RED)   // 叔叔节点为红色表示当前节点为4节点，分裂，爷爷节点进入上一层继续递归或者迭代
                {
                    u->color = BLACK;
                    p->color = BLACK;
                    g->color = RED;
                    x = g;                  // 继续迭代
                }
                else        // 叔叔节点不存在或叔叔节点为黑色
                {
                    if (x == p->right)
                    {
                        rotateLeft(p);
                        // 旋转后重置当前节点与双亲节点
                        Node *temp = x;
                        x = p;
                        p = temp;
                    }
                    g->color = RED;
                    p->color = BLACK;
                    rotateRight(g);
                    return;             // 修复完成
                }
            }
            else        // 双亲结点是爷爷节点的右孩子，也就是说当前节点插在爷爷节点的右子树上
            {
                Node *u = g->left;     // u表示叔叔节点
                if (u && u->color == RED)   // 叔叔节点为红色表示当前节点为4节点，分裂，爷爷节点进入上一层继续递归或者迭代
                {
                    u->color = BLACK;
                    p->color = BLACK;
                    g->color = RED;
                    x = g;                  // 继续迭代
                }
                else        // 叔叔节点不存在或叔叔节点为黑色
                {
                    if (x == p->left)
                    {
                        rotateRight(p);
                        // 旋转后重置当前节点与双亲节点
                        Node *temp = x;
                        x = p;
                        p = temp;
                    }
                    g->color = RED;
                    p->color = BLACK;
                    rotateLeft(g);
                    return;             // 修复完成
                }
            }
        }
        // 避免根节点为红色
        root->color = BLACK;
    }

    /** 插入：新插入的节点默认为红节点*/
    void insert(Key k, Value v)
    {
        Node *curr = root;
        Node *p = nullptr;     // 表示当前节点的双亲结点
        while (curr)
        {
            if (k < curr->key)
            {
                p = curr;
                curr = curr->left;
            }
            else if (k > curr->key)
            {
                p = curr;
                curr = curr->right;
            }
            else
            {
                curr->value = v;
                return;         // 该节点已经存在，更新该节点的值，插入完成
            }
        }

        Node *newNode = new Node(k, v);
        newNode->parent = p;
        if (p == nullptr)           // 说明为一空树
        {
            root = newNode;         // 更新根节点为新插入的节点
            root->color = BLACK;
            return;
        }
        else    // 树不空，新节点插在叶子结点p的左子节点或右子节点上
        {
            if (k < p->key) p->left = newNode;
            else p->right = newNode;

            // 插入后修复
            fixAfterInsert(newNode);
        }
    }

    /** 查找 */
    Node *find(Key k)
    {
        Node *p = root;
        while (p)
        {
            if (k < p->key) p = p->left;
            else if (k > p->key) p = p->right;
            else return p;
        }
        return nullptr;
    }
    /** Min */
    Node *Min(Node *node)
    {
        if (node == nullptr) return nullptr;
        while (node->left)
        {
            node = node->left;
        }
        return node;
    }
    Node *Min()
    {
        return Min(root);
    }
    /** Max */
    Node *Max(Node *node)
    {
        if (node == nullptr) return nullptr;
        while (node->right)
        {
            node = node->right;
        }
        return node;
    }
    Node *Max()
    {
        return Max(root);
    }
    /** 删除操作
     *  待删除的节点不存在，直接结束
     *  待删除的节点存在：
     *  （以下X表示待删除结点，B表示黑节点，R表示红节点）
     *      >> 1. 待删节点为叶子节点
     *
     *              (1)                          (2)                                            （3）
     *              BX              B3     B3           XB3    XB3                  B3          B3              XB3
     *   红黑树    /  \            /  \   /  \          /  \   /  \                /  \        /  \             /  \
     *                            XR1        XR5       R1         R5              R1  XR5     XR1 R5           R1  R5
     *
     *   2-3-4树    BX            XR1-B3  B3-XR5      R1-XB3  XB3-R5             R1-B3-XR5   XR1-B3-R5        R1-XB3-R5
     *
     *           需要调整         红节点直接删除    删除黑节点，用其子节点替代         红节点直接删除        同下面2， 可转化为2）
     *      >> 2. 待删除节点为非叶子节点，则必存在左右孩子节点，取其后继节点替代当前节点，问题转化为删除其后继节点，即1）或者2）
     *
     *  总结：先判断待删除节点是否有左右孩子，是的话将问题转化成1）、2）
     *  此时待处理的情况有三种， 1）、 2）、 3）的前半部分，继而转化为一下情况：
     *      >> 待删节点为红节点，直接删除
     *      >> 待删节点为一黑节点
     *          >> 有一个孩子，用孩子替代
     *          >> 没孩子，此时需要调整
     *          注意：待删节点为根节点的情况
     */
    void remove(Key k)
    {
        Node *node = find(k);

        if (node == nullptr) return;
        remove(node);
    }
    void remove(Node *x)
    {
        // 有俩孩子的情况（2-3-4树的中间节点或4节点叶子节点）
        // 通过转化将删除有两个孩子的节点转化为删除有一个孩子的节点或者没孩子的节点
       if (x->left && x->right)
        {
            Node *successor = Min(x->right);
            x->key = successor->key;
            x->value = successor->value;
            x = successor;           // node指向后继节点，将后继节点变为待删除的节点
        }

        if (x->color == RED)     /**< 待删除节点颜色为红色 */
        {
            if (x == x->parent->left) x->parent->left = nullptr;
            else x->parent->right = nullptr;
            delete x;
            return;
        }

        else   /**< 待删除节点颜色为黑色 */
        {
            if (x->left == nullptr && x->right == nullptr)  // 待删节点为一黑二节点
            {
                if (x == root)
                {
                    delete x;
                    root = nullptr;
                }
                else    // 需要先调整成3节点或4节点再删除
                {
                    // 先调整再删除,此时删除该节点不影响黑高
                    fixBeforeRemove(x);
                    if (x == x->parent->left) x->parent->left = nullptr;
                    else x->parent->right = nullptr;

                    delete x;
                }
            }
            else    // 待删节点有一个孩子节点，用孩子节点替代待删除结点
            {
                // 替代节点, 一定为红节点
                Node *r = x->left ? x->left : x->right;
                r->parent = x->parent;
                r->color = BLACK;       // 置为黑色以保持黑高
                if (x == root)          // 待删节点为根节点的情况
                {
                    root = r;
                }
                else
                {
                    if (x == x->parent->left) x->parent->left = r;
                    else x->parent->right = r;
                }
                delete x;
            }
        }

    /** 调整注意事项：
     * 1.（大前提：兄弟节点为一黑二节点，借不了）
     *  X表示待删除的节点，R表示红节点，B表示黑节点
     *                 （1）                  （2）                    （3）                                     （4）
     *             B4          B4        B4           B4             B6      B2               B4           B4          B4            B4
     *  红黑树    /  \        /  \      /  \         /  \           /  \    /  \             /   \        /   \       /   \         /   \
     *           XB1 B8      B1 XB8    XB1 R6       R2 XB8         R4  B8  B1  R4           R2   R6      R2   R6     R2   R6       R2   R6
     *                                    /  \     /  \           /  \        /  \         /  \ /  \    /  \ /  \   /  \ /  \     /  \ /  \
     *                                   B5  B8   B1  B3         XB1 B5      B3  XB8     XB1 B3 B5 B7  B1 XB3 B5 B7 B1 B3 XB5 B7  B1 B3 B5 XB7
     *                              这里的兄弟节点R6,R2为红节点
     *                              需要做一变换，变为（3）
     *
     *  2-3-4树    同上       同上        B4-R6       R2-B4         R4-B6        B2-R4                          R2-B4-R6
     *                                  /   |  \    /   |  \      /  |   \     /   |  \                       /  |   |  \
     *                                 XB1  B5  B8 B1  B3  XB8   XB1 B5   B8  B1  B3  XB8                    B1  B3  B5 B7  （X可为这下面任一个）
     *
     *  （1）（2）（3）（4）需要分别考虑左右两种情况，可仔细分析左边，编写完成后复制并对称修改即可
     *
     *
     *  （1）（3）（4）：兄弟节点帮不了，为达局部平衡，B8或者B1变为红色，然后x迭代向上指向其双亲节点B4 （即重复整个修复过程）
     *      退出条件：
     *             若一直递归到根节点，OK，此时不做处理，整体黑高减1，但是仍然平衡。
     *             若双亲节点为红色，即（3）中的情况，OK， 最后让双亲节点R4变为黑色，弥补了黑高的减少，黑高平衡。
     *             若双亲仍为黑色，则看此时兄弟节点是否可借，若可借，借1或2节点，黑高平衡，否则继续递归向上
     *
     *  （2）（3）：（2）中情况直接根据x->parent->left(or right)找到的并不是真正的（2-3-4树里的）最近的兄弟节点，
     *               因此需要首先做一下变化，交换当前兄弟节点与双亲结点的颜色，然后左旋/右旋，重置兄弟节点x->parent->left(or right)
     *               转化为（3）中情况， 执行上面步骤；
     *
     *
     * 2.兄弟节点有的借 （这里对左边节点删除加以分析，右边对称）
     *  共一下3种可能：
     *                    （3节点）                      （4节点）                   （最终结果）
     *                4                4                    4                           8
     *              /   \            /   \                /   \                       /   \
     *  2-3-4树    XB1  B8    --->  XB1  B8     ====     XB1  B8         ------>     B4   B9
     *                 /                   \                 /  \                   /  \
     *                R5                   R9               R5  R9                 XB1 R5
     *         交换兄弟节点与兄弟节点左子树的颜色     交换兄弟节点与双亲节点的颜色，并将兄弟节点的右孩子改成黑色一保持黑高
     *         然后右旋，变成右边的情况                                     左旋，此时X节点只需等待被删除即可
     *
     *  红黑树        4                4                    4                            8
     *              /   \            /   \                /   \                        /   \
     *            XB1  R5-B8       XB1  B8-R9           XB1 R5-B8-R9                 B4-R5 B9
     *                                                                               /
     *                                                                              XB1(之后被删掉，仍然黑高平衡)
     */
    }
    void fixBeforeRemove(Node *x)
    {
        while (x != root && x->color != RED)
        {
            if (x == x->parent->left)       // x是左孩子的情况
            {
                Node *s = x->parent->right;     // s表示兄弟节点（sibling）

                // 判断是否为真正的兄弟节点
                // 若找到的为2-3-4树中对应的兄弟节点，则对应的颜色应为黑色 （因为若为红节点的话，在2-3-4树里该节点在它上面一层，不是兄弟节点）
                // 即找到的是2-3-4树中双亲节点所在节点的其他键
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                }

                // 兄弟没的借，也是一黑色二节点
                if (s->left == nullptr && s->right == nullptr)
                {
                    s->color = RED;     // 为了删除后保持平衡（至少此局部平衡）令兄弟节点变红
                    x = x->parent;      // 该侧整体黑高减1，令待修复的节点迭代向上，若遇到红节点，红节点变黑弥补黑高否则一直向上直到根节点，整体黑高减一
                                        // 或者中间某一步，兄弟节点有的借，借一个（一黑）或两个（一红一黑）来弥补黑高
                }
                // 兄弟有的借，为黑3节点或4节点
                else
                {
                    // 3节点情况
                    // 红节点在左边
                    if (s->right == nullptr)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        rotateRight(s);
                        s = x->parent->right;       // 重置兄弟节点
                    }   //此时跟红节点在右边一致

                    // 对红节点在右边进行处理  （对四节点的情况也可以这样处理，只是此时借了两个节点）
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else        // x是右孩子的情况
            {
                Node *s = x->parent->left;     // s表示兄弟节点（sibling）

                // 判断是否为真正的兄弟节点
                // 若找到的为2-3-4树中对应的兄弟节点，则对应的颜色应为黑色
                // 反之找到的是2-3-4树中双亲节点所在节点的其他键
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    s = x->parent->left;        // 重置兄弟节点
                }

                // 兄弟没的借，也是一黑色二节点
                if (s->left == nullptr && s->right == nullptr)
                {
                    s->color = RED;     // 为了删除后保持平衡（至少此局部平衡）令兄弟节点变红
                    x = x->parent;      // 该侧整体黑高减1，令待修复的节点迭代向上，若遇到红节点，红节点变黑弥补黑高否则一直向上直到根节点，整体黑高减一
                }                       // 或者中间某一步，兄弟节点有的借，借一个（一黑）或两个（一红一黑）来弥补黑高
                // 兄弟有的借，为3节点或4节点
                else
                {
                    // 3节点情况
                    // 红节点在右边
                    if (s->left == nullptr)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        rotateLeft(s);
                        s = x->parent->left;       // 重置兄弟节点
                    }   //此时跟红节点在左边一致

                    // 对红节点在左边进行处理  （对四节点的情况也可以这样处理，只是此时借了两个节点）
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;          // 只是为了退出循环
                }
            }
        }

        x->color = BLACK;
    }
};

#endif // CLASSICALREDBLACKTREE_H_
