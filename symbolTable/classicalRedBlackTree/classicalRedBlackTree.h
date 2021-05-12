#ifndef CLASSICALREDBLACKTREE_H_
#define CLASSICALREDBLACKTREE_H_

/**************************************
����������ʵ��
1.ÿ�����Ҫô�Ǻ��Ҫô�Ǻڵġ�

2.������Ǻڵġ�

3.ÿ��Ҷ��㣨Ҷ��㼴ָ��β��NULL��㣩���Ǻڵġ�

4.���һ������Ǻ�ģ���ô�����������Ӷ��Ǻڵģ������������������ĺ�ڵ�

5.������������ԣ��䵽Ҷ�����β��NULLָ���ÿ��·����������ͬ��Ŀ�ĺڽ�㡣
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
        // ͨ���������ɾ�����ĸ����ڵ�
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
    // ǰ�����
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
    // �������
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
    // �������
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
    /** ������
     *     p                   p
     *     |                   |
     *     x                   y��rx��
     *    / \      ---->      / \
     *   lx  y��rx��         x   ry
     *      / \             / \
     *     ly  ry          lx  ly
     */
    void rotateLeft(Node *x)
    {
        if (x == nullptr || x->right == nullptr) return;

        Node *y = x->right;

        // �ȴ���ڵ�ly���, ���ڵ�x���Һ��ӵ�����
        x->right = y->left;
        if (y->left) y->left->parent = x;

        // ����ڵ�y
        y->left = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;   // ˵��Ϊ���ڵ㣬���������ֻ�и��ڵ�û��˫�׽ڵ�
        }
        else
        {
            if (x == x->parent->left) x->parent->left = y;
            else x->parent->right = y;
        }

        // �����x�ڵ�
        x->parent = y;
    }

    /** ������
     *          p                       p
     *          |                       |
     *          y                       x��ly��       ���е�x��y�ڵ����Ϊp�����ֻ��Һ��ӽڵ㣬Ҳ����Ϊ���ڵ㣨���pΪ�յĻ���
     *         / \          ---->      / \
     *  ��ly��x   ry                  lx  y
     *       / \                         / \
     *     lx  ly                      ly  ry
     */
    void rotateRight(Node *y)
    {
        if (y == nullptr || y->left == nullptr) return;

        Node *x = y->left;

        // �ȴ���ڵ�ly���
        if (x->right) x->right->parent = y;
        y->left = x->right;

        // ����x�ڵ�
        x->right = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
        {
            root = x;   // ˵��Ϊ���ڵ�,���¸��ڵ�
        }
        else
        {
            if (y == y->parent->left) y->parent->left = x;
            else y->parent->right = x;
        }

        // �����y�ڵ�
        y->parent = x;
    }

    /** ������޸�
    *
    * ����3�ڵ��4�ڵ㣬�ȶ�״̬һ�����Ϻ��º�,�������ĺ�ڵ�����˫�׺ڽڵ��ڶ���������Ϊһ��3�ڵ����4�ڵ�
    *
    * �����²���Ԫ�ر�ʾΪX, B��ʾ�ڽڵ㣬 R��ʾ��ڵ�
    *
    * 1.���ڵ�����ڵ㣬 �������߻�����ұߣ�ֱ�Ӳ��룬����Ҫ����
    *             B2              B2
    *  �����     /                \
    *            XR1               XR3
    *
    *  2-3-4��  XR1-B2           B2-XR3
    *
    * 2. ���ڵ���Ľڵ�
    * 2.1            (1)����үү�ڵ����������              (2)����үү�ڵ����������                     ��3��
    *             B5                     B5                 B3                      B3                         B5                B5
    *             /                      /                    \                      \                        /  \              /  \
    *            R3  ------>  B3        R3        ......      R5       ......         R5     ......          R3  XR7          XR3  R7
    *           /            /  \        \                      \                     /
    *          XR1          XR1 R5      XR4                     XR7                  XR4
    *                             ��ͨ��������Ϊǰһ�����                     ��ͨ��������Ϊǰһ�����    ��������ں������������ڣ���������
    *  2-3-4��    XR1-R3-B5           R3-XR4---B5              B3-R5-XR7           B3---XR4-R5               R3-B5-XR7         XR3-B5-R7
    *
    * 3. �Ľڵ������������ӽڵ���˫�׽ڵ���
    * 1����ɫ�任
    *           B5              R5         B5              R5                     B5              R5            B5              R5
    *          /  \            /  \       /  \            /  \                   /  \            /  \          /  \            /  \
    *         R3  R7 ------>  B3  B7     R3  R7 ------>  B3  B7                 R3  R7 ------>  B3  B7        R3  R7 ------>  B3  B7
    *        /               /            \               \                           \               \            /              /
    *       R1              R1            R4             R4                           XR9             XR9         XR6            XR6
    * 2��ת��Ϊ�ڶ��ڵ��ϲ���һ���½ڵ��Ϊ���ڵ�����⣬���ڵ��Ϊ3�ڵ㵱ǰ�ڵ㲻��Ҫ�任�� �������ĺ�ڵ���ܻᵼ�¸��ڵ�ĵ������ݹ���������
    *
    *
    * �ܽᣬ ˫�׽ڵ�Ϊ�ڣ�����Ҫ������
    * ֻ��˫�׽ڵ�Ϊ��ʱ����Ҫ����������Ϊ����������
    * >> ˫�׽����үү�ڵ������
    *
    *   >> ����ڵ�Ϊ��ɫ��ֱ�ӱ�ɫ��үү�ڵ㣬����ڵ㣬˫�׽ڵ㣩��үү�ڵ�����ܻ�Ӱ���ϲ����Ľṹ���ݹ��������ϴ���
    *   >> ����ڵ�Ϊ��ɫ
    *       >> ��ǰ�ڵ�Ϊ˫�׽ڵ�����ӣ�����үү�ڵ���˫�׽ڵ����ɫ���������޸����
    *       >> ��ǰ�ڵ�Ϊ˫�׽ڵ���Һ��ӣ�������ǰ�ڵ���˫�׽ڵ����ɫ����������ת֮���Ϊ��һ�����
    *
    * >> ˫�׽����үү�ڵ���Һ���
    *
    *   >> ����ڵ�Ϊ��ɫ��ֱ�ӱ�ɫ��үү�ڵ㣬����ڵ㣬˫�׽ڵ㣩��үү�ڵ�����ܻ�Ӱ���ϲ����Ľṹ���ݹ��������ϴ���
    *   >> ����ڵ�Ϊ��ɫ
    *       >> ��ǰ�ڵ�Ϊ˫�׽ڵ���Һ��ӣ�����үү�ڵ���˫�׽ڵ����ɫ���������޸����
    *       >> ��ǰ�ڵ�Ϊ˫�׽ڵ�����ӣ�������ǰ�ڵ���˫�׽ڵ����ɫ����������ת֮���Ϊ��һ�����
    *
    * >>>> ע�⣺��ǰ�ڵ�Ϊ���ڵ�ʱ����ɫ��ڣ���Ϊ���ڵ�Ҫ����Ϊ��ɫ
    */
    void fixAfterInsert(Node *x)
    {
        while (x != root && x->parent->color == RED)
        {   // x != root�ȼ���x->parent != nullptr ��ʾ˫�׽ڵ����,����˫�׽��Ϊ��ڵ��ʾүү�ڵ�һ�����ڣ��Ϻ��º죬�ȶ�״̬�º�ڵ��ڶ��������ﲻ�ܵ�������
            Node *p = x->parent;     // p��ʾ˫��
            Node *g = p->parent;     // g��ʾүү�ڵ�
            if (p == g->left)
            {
                Node *u = g->right;     // u��ʾ����ڵ�
                if (u && u->color == RED)   // ����ڵ�Ϊ��ɫ��ʾ��ǰ�ڵ�Ϊ4�ڵ㣬���ѣ�үү�ڵ������һ������ݹ���ߵ���
                {
                    u->color = BLACK;
                    p->color = BLACK;
                    g->color = RED;
                    x = g;                  // ��������
                }
                else        // ����ڵ㲻���ڻ�����ڵ�Ϊ��ɫ
                {
                    if (x == p->right)
                    {
                        rotateLeft(p);
                        // ��ת�����õ�ǰ�ڵ���˫�׽ڵ�
                        Node *temp = x;
                        x = p;
                        p = temp;
                    }
                    g->color = RED;
                    p->color = BLACK;
                    rotateRight(g);
                    return;             // �޸����
                }
            }
            else        // ˫�׽����үү�ڵ���Һ��ӣ�Ҳ����˵��ǰ�ڵ����үү�ڵ����������
            {
                Node *u = g->left;     // u��ʾ����ڵ�
                if (u && u->color == RED)   // ����ڵ�Ϊ��ɫ��ʾ��ǰ�ڵ�Ϊ4�ڵ㣬���ѣ�үү�ڵ������һ������ݹ���ߵ���
                {
                    u->color = BLACK;
                    p->color = BLACK;
                    g->color = RED;
                    x = g;                  // ��������
                }
                else        // ����ڵ㲻���ڻ�����ڵ�Ϊ��ɫ
                {
                    if (x == p->left)
                    {
                        rotateRight(p);
                        // ��ת�����õ�ǰ�ڵ���˫�׽ڵ�
                        Node *temp = x;
                        x = p;
                        p = temp;
                    }
                    g->color = RED;
                    p->color = BLACK;
                    rotateLeft(g);
                    return;             // �޸����
                }
            }
        }
        // ������ڵ�Ϊ��ɫ
        root->color = BLACK;
    }

    /** ���룺�²���Ľڵ�Ĭ��Ϊ��ڵ�*/
    void insert(Key k, Value v)
    {
        Node *curr = root;
        Node *p = nullptr;     // ��ʾ��ǰ�ڵ��˫�׽��
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
                return;         // �ýڵ��Ѿ����ڣ����¸ýڵ��ֵ���������
            }
        }

        Node *newNode = new Node(k, v);
        newNode->parent = p;
        if (p == nullptr)           // ˵��Ϊһ����
        {
            root = newNode;         // ���¸��ڵ�Ϊ�²���Ľڵ�
            root->color = BLACK;
            return;
        }
        else    // �����գ��½ڵ����Ҷ�ӽ��p�����ӽڵ�����ӽڵ���
        {
            if (k < p->key) p->left = newNode;
            else p->right = newNode;

            // ������޸�
            fixAfterInsert(newNode);
        }
    }

    /** ���� */
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
    /** ɾ������
     *  ��ɾ���Ľڵ㲻���ڣ�ֱ�ӽ���
     *  ��ɾ���Ľڵ���ڣ�
     *  ������X��ʾ��ɾ����㣬B��ʾ�ڽڵ㣬R��ʾ��ڵ㣩
     *      >> 1. ��ɾ�ڵ�ΪҶ�ӽڵ�
     *
     *              (1)                          (2)                                            ��3��
     *              BX              B3     B3           XB3    XB3                  B3          B3              XB3
     *   �����    /  \            /  \   /  \          /  \   /  \                /  \        /  \             /  \
     *                            XR1        XR5       R1         R5              R1  XR5     XR1 R5           R1  R5
     *
     *   2-3-4��    BX            XR1-B3  B3-XR5      R1-XB3  XB3-R5             R1-B3-XR5   XR1-B3-R5        R1-XB3-R5
     *
     *           ��Ҫ����         ��ڵ�ֱ��ɾ��    ɾ���ڽڵ㣬�����ӽڵ����         ��ڵ�ֱ��ɾ��        ͬ����2�� ��ת��Ϊ2��
     *      >> 2. ��ɾ���ڵ�Ϊ��Ҷ�ӽڵ㣬��ش������Һ��ӽڵ㣬ȡ���̽ڵ������ǰ�ڵ㣬����ת��Ϊɾ�����̽ڵ㣬��1������2��
     *
     *  �ܽ᣺���жϴ�ɾ���ڵ��Ƿ������Һ��ӣ��ǵĻ�������ת����1����2��
     *  ��ʱ���������������֣� 1���� 2���� 3����ǰ�벿�֣��̶�ת��Ϊһ�������
     *      >> ��ɾ�ڵ�Ϊ��ڵ㣬ֱ��ɾ��
     *      >> ��ɾ�ڵ�Ϊһ�ڽڵ�
     *          >> ��һ�����ӣ��ú������
     *          >> û���ӣ���ʱ��Ҫ����
     *          ע�⣺��ɾ�ڵ�Ϊ���ڵ�����
     */
    void remove(Key k)
    {
        Node *node = find(k);

        if (node == nullptr) return;
        remove(node);
    }
    void remove(Node *x)
    {
        // �������ӵ������2-3-4�����м�ڵ��4�ڵ�Ҷ�ӽڵ㣩
        // ͨ��ת����ɾ�����������ӵĽڵ�ת��Ϊɾ����һ�����ӵĽڵ����û���ӵĽڵ�
       if (x->left && x->right)
        {
            Node *successor = Min(x->right);
            x->key = successor->key;
            x->value = successor->value;
            x = successor;           // nodeָ���̽ڵ㣬����̽ڵ��Ϊ��ɾ���Ľڵ�
        }

        if (x->color == RED)     /**< ��ɾ���ڵ���ɫΪ��ɫ */
        {
            if (x == x->parent->left) x->parent->left = nullptr;
            else x->parent->right = nullptr;
            delete x;
            return;
        }

        else   /**< ��ɾ���ڵ���ɫΪ��ɫ */
        {
            if (x->left == nullptr && x->right == nullptr)  // ��ɾ�ڵ�Ϊһ�ڶ��ڵ�
            {
                if (x == root)
                {
                    delete x;
                    root = nullptr;
                }
                else    // ��Ҫ�ȵ�����3�ڵ��4�ڵ���ɾ��
                {
                    // �ȵ�����ɾ��,��ʱɾ���ýڵ㲻Ӱ��ڸ�
                    fixBeforeRemove(x);
                    if (x == x->parent->left) x->parent->left = nullptr;
                    else x->parent->right = nullptr;

                    delete x;
                }
            }
            else    // ��ɾ�ڵ���һ�����ӽڵ㣬�ú��ӽڵ������ɾ�����
            {
                // ����ڵ�, һ��Ϊ��ڵ�
                Node *r = x->left ? x->left : x->right;
                r->parent = x->parent;
                r->color = BLACK;       // ��Ϊ��ɫ�Ա��ֺڸ�
                if (x == root)          // ��ɾ�ڵ�Ϊ���ڵ�����
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

    /** ����ע�����
     * 1.����ǰ�᣺�ֵܽڵ�Ϊһ�ڶ��ڵ㣬�費�ˣ�
     *  X��ʾ��ɾ���Ľڵ㣬R��ʾ��ڵ㣬B��ʾ�ڽڵ�
     *                 ��1��                  ��2��                    ��3��                                     ��4��
     *             B4          B4        B4           B4             B6      B2               B4           B4          B4            B4
     *  �����    /  \        /  \      /  \         /  \           /  \    /  \             /   \        /   \       /   \         /   \
     *           XB1 B8      B1 XB8    XB1 R6       R2 XB8         R4  B8  B1  R4           R2   R6      R2   R6     R2   R6       R2   R6
     *                                    /  \     /  \           /  \        /  \         /  \ /  \    /  \ /  \   /  \ /  \     /  \ /  \
     *                                   B5  B8   B1  B3         XB1 B5      B3  XB8     XB1 B3 B5 B7  B1 XB3 B5 B7 B1 B3 XB5 B7  B1 B3 B5 XB7
     *                              ������ֵܽڵ�R6,R2Ϊ��ڵ�
     *                              ��Ҫ��һ�任����Ϊ��3��
     *
     *  2-3-4��    ͬ��       ͬ��        B4-R6       R2-B4         R4-B6        B2-R4                          R2-B4-R6
     *                                  /   |  \    /   |  \      /  |   \     /   |  \                       /  |   |  \
     *                                 XB1  B5  B8 B1  B3  XB8   XB1 B5   B8  B1  B3  XB8                    B1  B3  B5 B7  ��X��Ϊ��������һ����
     *
     *  ��1����2����3����4����Ҫ�ֱ��������������������ϸ������ߣ���д��ɺ��Ʋ��Գ��޸ļ���
     *
     *
     *  ��1����3����4�����ֵܽڵ�ﲻ�ˣ�Ϊ��ֲ�ƽ�⣬B8����B1��Ϊ��ɫ��Ȼ��x��������ָ����˫�׽ڵ�B4 �����ظ������޸����̣�
     *      �˳�������
     *             ��һֱ�ݹ鵽���ڵ㣬OK����ʱ������������ڸ߼�1��������Ȼƽ�⡣
     *             ��˫�׽ڵ�Ϊ��ɫ������3���е������OK�� �����˫�׽ڵ�R4��Ϊ��ɫ���ֲ��˺ڸߵļ��٣��ڸ�ƽ�⡣
     *             ��˫����Ϊ��ɫ���򿴴�ʱ�ֵܽڵ��Ƿ�ɽ裬���ɽ裬��1��2�ڵ㣬�ڸ�ƽ�⣬��������ݹ�����
     *
     *  ��2����3������2�������ֱ�Ӹ���x->parent->left(or right)�ҵ��Ĳ����������ģ�2-3-4����ģ�������ֵܽڵ㣬
     *               �����Ҫ������һ�±仯��������ǰ�ֵܽڵ���˫�׽�����ɫ��Ȼ������/�����������ֵܽڵ�x->parent->left(or right)
     *               ת��Ϊ��3��������� ִ�����沽�裻
     *
     *
     * 2.�ֵܽڵ��еĽ� ���������߽ڵ�ɾ�����Է������ұ߶Գƣ�
     *  ��һ��3�ֿ��ܣ�
     *                    ��3�ڵ㣩                      ��4�ڵ㣩                   �����ս����
     *                4                4                    4                           8
     *              /   \            /   \                /   \                       /   \
     *  2-3-4��    XB1  B8    --->  XB1  B8     ====     XB1  B8         ------>     B4   B9
     *                 /                   \                 /  \                   /  \
     *                R5                   R9               R5  R9                 XB1 R5
     *         �����ֵܽڵ����ֵܽڵ�����������ɫ     �����ֵܽڵ���˫�׽ڵ����ɫ�������ֵܽڵ���Һ��Ӹĳɺ�ɫһ���ֺڸ�
     *         Ȼ������������ұߵ����                                     ��������ʱX�ڵ�ֻ��ȴ���ɾ������
     *
     *  �����        4                4                    4                            8
     *              /   \            /   \                /   \                        /   \
     *            XB1  R5-B8       XB1  B8-R9           XB1 R5-B8-R9                 B4-R5 B9
     *                                                                               /
     *                                                                              XB1(֮��ɾ������Ȼ�ڸ�ƽ��)
     */
    }
    void fixBeforeRemove(Node *x)
    {
        while (x != root && x->color != RED)
        {
            if (x == x->parent->left)       // x�����ӵ����
            {
                Node *s = x->parent->right;     // s��ʾ�ֵܽڵ㣨sibling��

                // �ж��Ƿ�Ϊ�������ֵܽڵ�
                // ���ҵ���Ϊ2-3-4���ж�Ӧ���ֵܽڵ㣬���Ӧ����ɫӦΪ��ɫ ����Ϊ��Ϊ��ڵ�Ļ�����2-3-4����ýڵ���������һ�㣬�����ֵܽڵ㣩
                // ���ҵ�����2-3-4����˫�׽ڵ����ڽڵ��������
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    s = x->parent->right;
                }

                // �ֵ�û�Ľ裬Ҳ��һ��ɫ���ڵ�
                if (s->left == nullptr && s->right == nullptr)
                {
                    s->color = RED;     // Ϊ��ɾ���󱣳�ƽ�⣨���ٴ˾ֲ�ƽ�⣩���ֵܽڵ���
                    x = x->parent;      // �ò�����ڸ߼�1������޸��Ľڵ�������ϣ���������ڵ㣬��ڵ����ֲ��ڸ߷���һֱ����ֱ�����ڵ㣬����ڸ߼�һ
                                        // �����м�ĳһ�����ֵܽڵ��еĽ裬��һ����һ�ڣ���������һ��һ�ڣ����ֲ��ڸ�
                }
                // �ֵ��еĽ裬Ϊ��3�ڵ��4�ڵ�
                else
                {
                    // 3�ڵ����
                    // ��ڵ������
                    if (s->right == nullptr)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        rotateRight(s);
                        s = x->parent->right;       // �����ֵܽڵ�
                    }   //��ʱ����ڵ����ұ�һ��

                    // �Ժ�ڵ����ұ߽��д���  �����Ľڵ�����Ҳ������������ֻ�Ǵ�ʱ���������ڵ㣩
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }
            }
            else        // x���Һ��ӵ����
            {
                Node *s = x->parent->left;     // s��ʾ�ֵܽڵ㣨sibling��

                // �ж��Ƿ�Ϊ�������ֵܽڵ�
                // ���ҵ���Ϊ2-3-4���ж�Ӧ���ֵܽڵ㣬���Ӧ����ɫӦΪ��ɫ
                // ��֮�ҵ�����2-3-4����˫�׽ڵ����ڽڵ��������
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    s = x->parent->left;        // �����ֵܽڵ�
                }

                // �ֵ�û�Ľ裬Ҳ��һ��ɫ���ڵ�
                if (s->left == nullptr && s->right == nullptr)
                {
                    s->color = RED;     // Ϊ��ɾ���󱣳�ƽ�⣨���ٴ˾ֲ�ƽ�⣩���ֵܽڵ���
                    x = x->parent;      // �ò�����ڸ߼�1������޸��Ľڵ�������ϣ���������ڵ㣬��ڵ����ֲ��ڸ߷���һֱ����ֱ�����ڵ㣬����ڸ߼�һ
                }                       // �����м�ĳһ�����ֵܽڵ��еĽ裬��һ����һ�ڣ���������һ��һ�ڣ����ֲ��ڸ�
                // �ֵ��еĽ裬Ϊ3�ڵ��4�ڵ�
                else
                {
                    // 3�ڵ����
                    // ��ڵ����ұ�
                    if (s->left == nullptr)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        rotateLeft(s);
                        s = x->parent->left;       // �����ֵܽڵ�
                    }   //��ʱ����ڵ������һ��

                    // �Ժ�ڵ�����߽��д���  �����Ľڵ�����Ҳ������������ֻ�Ǵ�ʱ���������ڵ㣩
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;          // ֻ��Ϊ���˳�ѭ��
                }
            }
        }

        x->color = BLACK;
    }
};

#endif // CLASSICALREDBLACKTREE_H_
