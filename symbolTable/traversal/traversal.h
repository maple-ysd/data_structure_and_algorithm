#ifndef TRAVERSAL_H_
#define TRAVERSAL_H_

/********************************************
�������ı���
*********************************************/


#include <string>
#include <iostream>
#include <stack>    // �ǵݹ����Ҫ��
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
// ����
Node *buildTree(Key *keys, Value *values, int n)
{
    if (n <= 0) return nullptr;
    Node *root = new Node(keys[0], values[0]);
    Node *p = root;     // �����������Ҵ������λ��
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
                if (p->left) p = p->left;       // ���Ϊ�գ�ֱ�Ӳ�����ߣ�����p=p->left��������
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
    // �������ɾ��
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
�ݹ����
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
�ǵݹ����
****************/

void preOrderTraversal2(Node *root)
{
    std::stack<Node*> st;
    Node *p = root;
    while (p || !st.empty())
    {
        // һֱ�����߲�ѹջ���
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
            // һֱ�����ߣ�ѹջ�������
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

// ��һ���ڵ����prev����¼��һ�����ʹ��Ľڵ�
// �����ǰջ���Ľڵ���Һ��Ӹպ���prev�����Һ���Ϊ�գ����������ջ�� ����prevΪ�շ��ʹ�������ڵ�
// �����Һ�����δ���ʹ���ջ��Ԫ�ز���ջ�����µ����ڵ�pΪ�����Һ���
void postOrderTraversal2(Node *root)
{
    std::stack<Node*> st;
    Node *temp = nullptr;
    Node *p = root;
    Node *prev = nullptr;      // ��Ҫ�����ж�ǰһ�������ӡ�Ľڵ��Ƿ�Ϊ��ǰ�ڵ���Һ���
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

// ��һ�ַ�ʽʵ�ֺ����ǵݹ����
// ѹջʱ��һ��bool�����뵱ǰ�ڵ�ָ�������ѹ�룬���ݸ�bool�����ж�ջ����ʱ��ջ

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

// ��������ַǵݹ�ʵ��
// 1��ʵ�ֺ�������
// ���ݺ������������ԣ���->��->��, ��תһ�±�Ϊ��->��->��
// ��ģ��ǰ�������������ֻ�����һֱ�����߶����������ߣ���������;���Ľڵ�ѹջ��������ջҲ�������
// ��ȫ����ջ���ٰ�����ջ����ӡ
// ȱ����ջ�����Ҫ���Կռ���

// 2��ʵ�����������ͨ����������ռ�
// �ı�ڵ�֮�������
// �����ڵ��ʼ��Ϊroot�ڵ㣬�ýڵ�Ϊ��ʱ�˳�
// �����ǰ�ڵ������ӣ��򽫵�ǰ�ڵ���������ӵ����ڵ���ҽڵ��ϣ� �����ڵ����Ϊ��ǰ�ڵ������
// ����Ļ�����ӡ�����ǰ�ڵ㣬���������ڵ����Ϊ�����Һ���

#endif // TRAVERSAL_H_
