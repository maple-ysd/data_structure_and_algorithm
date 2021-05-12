#ifndef TERNARYSEARCHTRIE_H_
#define TERNARYSEARCHTRIE_H_

#include <string>
#include <vector>
#include <queue>

template <typename Value>
class TernarySearchTrie
{
    const int Null = Value();
    struct Node
    {
        char character;
        Value value;
        int Size = 0;

        Node *left = nullptr;
        Node *middle = nullptr;
        Node *right = nullptr;
    };
public:
    TernarySearchTrie(): Size(0), root(nullptr) {}
    ~TernarySearchTrie()
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
                if (temp->middle) que.push(temp->middle);
                if (temp->right) que.push(temp->right);
                delete temp;
            }
        }
    }
    int size() { return Size; }
    bool empty() { return size() == 0; }
    bool contains(std::string key)
    {
        return find(key) != nullptr;
    }
    Node *find(std::string key)
    {
        Node *node = find(root, key, 0);
        if (node == nullptr)
            return nullptr;
        return node;
    }
    void put(std::string key, Value v)
    {
        Node *node = find(key);
        if (node != nullptr) node->value = v;
        else
        {
            root = put(root, key, v, 0);
            ++Size;
        }
    }
    void Delete(std::string key)
    {
        if (!contains(key)) return;

        root = Delete(root, key, 0);
        --Size;
    }
    std::vector<std::string> keys()
    {
        std::vector<std::string> vs;
        collect(root, std::string(""), vs);
        return vs;
    }
    std::vector<std::string> keysWithPrefix(std::string prefix)
    {
        std::vector<std::string> vs;
        Node *node = find(root, prefix, 0);
        if (node == nullptr) return vs;
        else
        {
            vs.push_back(prefix);
        }
        collect(node->middle, prefix, vs);
        return vs;
    }
    std::vector<std::string> keysThatMatch(std::string pattern)
    {
        std::vector<std::string> vs;
        collect(root, std::string(""), pattern, vs);
        return vs;
    }
    std::string longestPrefixOf(std::string query)
    {
        int length = search(root, query, 0, 0);
        return query.substr(0, length);
    }
private:
    Node *find(Node *node, std::string key, int digit)
    {
        if (node == nullptr) return nullptr;

        int currChar = key[digit];
        if (currChar < node->character)
            return find(node->left, key, digit);
        else if (currChar > node->character)
            return find(node->right, key, digit);
        else if (digit < key.size() - 1)
            return find(node->middle, key, digit + 1);
        else
            return node;
    }
    Node *put(Node *node, std::string key, Value v, int digit)
    {
        int currChar = key[digit];
        if (node == nullptr)
        {
            node = new Node;
            node->character = currChar;
        }
        if (currChar < node->character)
            node->left = put(node->left, key, v, digit);
        else if (currChar > node->character)
            node->right = put(node->right, key, v, digit);
        else if (digit < key.size() - 1)
        {
            node->middle = put(node->middle, key, v, digit + 1);
            ++node->Size;
        }
        else
        {
            node->value = v;
            ++node->Size;
        }
        return node;
    }
    Node *Delete(Node *node, std::string key, int digit)
    {

        int nextChar = key[digit];
        if (nextChar < node->character)
            node->left = Delete(node->left, key, digit);
        else if (nextChar > node->character)
            node->right = Delete(node->right, key, digit);
        else if (digit == key.size() - 1)
        {
            node->value = Null;
            --node->Size;
        }
        else
        {
            --node->Size;
            node->middle = Delete(node->middle, key, digit + 1);
        }

        if (node->Size == 0)
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                Node *aux = Min(node->right);
                aux->left = node->left;
                aux->right = deleteMin(node->right);
                delete node;
                node = aux;
            }
        }
        return node;
    }
    void collect(Node *node, std::string prefix, std::vector<std::string> &vs)
    {
        if (node == nullptr) return;
        collect(node->left, prefix, vs);
        if (node->value != Null) vs.push_back(prefix + node->character);
        collect(node->middle, prefix + node->character, vs);
        collect(node->right, prefix, vs);
    }
    void collect(Node *node, std::string prefix, std::string pattern, std::vector<std::string> &vs)
    {
        if (node == nullptr) return;
        int digit = prefix.size();

        char nextCharInPattern = pattern[digit];
        if (nextCharInPattern == '.' || nextCharInPattern < node->character)
        {
            collect(node->left, prefix, pattern, vs);
        }
        if (nextCharInPattern == '.' || nextCharInPattern == node->character)
        {
            if (digit == pattern.size() - 1 && node->value != Null)
                vs.push_back(prefix + node->character);
            else if (digit < pattern.size() - 1)
            {
                collect(node->middle, prefix + node->character, pattern, vs);
            }
        }
        if (nextCharInPattern == '.' || nextCharInPattern > node->character)
        {
            collect(node->right, prefix, pattern, vs);
        }
    }
    int search(Node *node, std::string query, int digit, int length)
    {
        if (node == nullptr) return length;

        int nextChar = query[digit];
        if (nextChar < node->character)
            return search(node->left, query, digit, length);
        else if (nextChar > node->character)
            return search(node->right, query, digit, length);
        else if (digit < query.size() - 1)
        {
            if (node->value != Null) length = digit + 1;
            return search(node->middle, query, digit + 1, length);
        }
        else
        {
            if (node->value != Null) length = digit + 1;
            return length;
        }
    }
    Node *Min(Node *node)
    {
        if (node->left == nullptr) return node;
        return Min(node->left);
    }
    Node *deleteMin(Node *node)
    {
        if (node->left == nullptr) return node->right;
        node->left = deleteMin(node->left);
        return node;
    }
    int Size;
    Node *root;
};


#endif // TERNARYSEARCHTRIE_H_
