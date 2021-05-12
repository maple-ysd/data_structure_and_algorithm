#ifndef TRAVERSAL_H_
#define TRAVERSAL_H_

/********************************************
二叉树的遍历
*********************************************/


#include <string>
#include <iostream>
#include <stack>    // 非递归遍历要用
#include <utility>  // pair
#include <queue>
typedef std::string Key;
typedef int Value;
struct Node
{
    Key key;
    Value value;
    Node *left;
    Node *right;
    Node(Key k, Value v): key(k), value(v), left(nullptr), right(nullptr){}
};
// 建树
Node *buildTree(Key *keys, Value *values, int n)
{
    if (n <= 0) return nullptr;
    Node *root = new Node(keys[0], values[0]);
    Node *p = root;     // 用来迭代查找待插入的位置
    for (int i = 1; i < n; ++i)
    {
        p = root;
        while (p)
        {
            if (p->key == keys[i])
            {
                p->value = values[i];
                break;
            }
            else if (p->key > keys[i])
            {
                if (p->left) p = p->left;       // 如果为空，直接插在左边，否则p=p->left继续迭代
                else
                {
                    p->left = new Node(keys[i], values[i]);
                    break;
                }
            }
            else
            {
                if (p->right) p = p->right;
                else
                {
                    p->right = new Node(keys[i], values[i]);
                    break;
                }
            }
        }
    }
    return root;
}

void deleteTree(Node *root)
{
    // 层序遍历删除
    std::queue<Node*> que;
    Node *temp = nullptr;
    if (!root) return;
    que.push(root);
    while (!que.empty())
    {
        temp = que.front();
        que.pop();
        if (temp->left) que.push(temp->left);
        if (temp->right) que.push(temp->right);
        delete temp;
    }
}
/****************
递归遍历
*****************/
void preOrderTraversal(Node *root)
{
    if (!root) return;
    std::cout << root->key << " " << root->value << "    ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}
void inOrderTraversal(Node *root)
{
    if (!root) return;
    inOrderTraversal(root->left);
    std::cout << root->key << " " << root->value << "    ";
    inOrderTraversal(root->right);
}
void postOrderTraversal(Node *root)
{
    if (!root) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    std::cout << root->key << " " << root->value << "    ";
}

/***************
非递归遍历
****************/

void preOrderTraversal2(Node *root)
{
    std::stack<Node*> st;
    Node *p = root;
    while (p || !st.empty())
    {
        // 一直往左走并压栈输出
        while (p)
        {
            std::cout << p->key << " " << p->value << "    ";
            st.push(p);
            p = p->left;
        }
        if (!st.empty())
        {
            p = st.top()->right;
            st.pop();
        }
    }
}

void inOrderTraversal2(Node *root)
{
    std::stack<Node*> st;
    Node *temp = nullptr;
    Node *p = root;
    while (p || !st.empty())
    {
        while (p)
        {
            // 一直往左走，压栈但不输出
            st.push(p);
            p = p->left;
        }
        if (!st.empty())
        {
            temp = st.top();
            std::cout << temp->key << " " << temp->value << "    ";
            p = temp->right;
            st.pop();
        }
    }
}

// 用一个节点变量prev来记录上一个访问过的节点
// 如果当前栈顶的节点的右孩子刚好是prev或者右孩子为空，则输出并出栈， 更新prev为刚访问过的这个节点
// 否则，右孩子尚未访问过，栈顶元素不出栈，更新迭代节点p为它的右孩子
void postOrderTraversal2(Node *root)
{
    std::stack<Node*> st;
    Node *temp = nullptr;
    Node *p = root;
    Node *prev = nullptr;      // 主要用于判断前一个输出打印的节点是否为当前节点的右孩子
    while (p || !st.empty())
    {
        while (p)
        {
            st.push(p);
            p = p->left;
        }
        if (!st.empty())
        {
            temp = st.top();
            if (temp->right == nullptr || temp->right == prev)
            {
                std::cout << temp->key << " " << temp->value << "    ";
                prev = temp;
                st.pop();
            }
            else
                p = temp->right;
        }
    }
}

// 另一种方式实现后续非递归遍历
// 压栈时将一个bool变量与当前节点指针合起来压入，根据该bool变量判断栈顶何时出栈

void postOrderTraversal3(Node *root)
{
    std::stack<std::pair<Node*, bool>> st;
    Node *p = root;
    std::pair<Node*, bool> temp;
    while (p || !st.empty())
    {
        while (p)
        {
            st.push(std::make_pair(p, false));
            p = p->left;
        }
        if (!st.empty())
        {
            temp = st.top();
            st.pop();
            if (!temp.second)
            {
                temp.second = true;
                st.push(temp);
                p = temp.first->right;
            }
            else
            {
                std::cout << temp.first->key << " " << temp.first->value << "    ";

            }
        }
    }
}

// 另外的两种非递归实现
// 1：实现后续遍历
// 根据后续遍历的特性：左->右->根, 翻转一下变为根->右->左
// 将模仿前序遍历，（区别只是这次一直往右走而不是往左走），将所有途径的节点压栈，但不出栈也不输出；
// 等全部入栈后，再挨个出栈并打印
// 缺点是栈这次需要线性空间了

// 2：实现中序遍历，通过常量额外空间
// 改变节点之间的链接
// 迭代节点初始化为root节点，该节点为空时退出
// 如果当前节点有左孩子，则将当前节点挂在其左孩子的最大节点的右节点上， 迭代节点更新为当前节点的左孩子
// 否则的话，打印输出当前节点，并将迭代节点更新为它的右孩子

#endif // TRAVERSAL_H_
