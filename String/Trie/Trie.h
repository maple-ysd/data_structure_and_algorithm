#ifndef TRIE_H_
#define TRIE_H_

#include <vector>
#include <string>
#include <queue>

template <typename Value>
class Trie
{
    // 将默认的Value（）构造函数值作为空
    const Value Null = Value();
    //
    static const int R = 128;
    struct Node
    {
        Value value;
        std::vector<Node*> next;
        int Size;
        Node(): value(Value()), next(std::vector<Node *>(R)), Size(0)
        {
            for (int i = 0; i < R; ++i)
                next[i] = nullptr;
        }
    };
private:
    Node *root;
public:
    Trie(): root(nullptr) {}
    ~Trie()
    {
        if (root)
        {
            std::queue<Node *> q;
            q.push(root);
            while (!q.empty())
            {
                Node *temp = q.front();
                q.pop();
                for (int i = 0; i < R; ++i)
                    if (temp->next[i] != nullptr) q.push(temp->next[i]);
                delete temp;
            }
        }
    }
    int size() { return size(root); }
private:
    int size(Node *node)
    {
        if (node == nullptr)
            return 0;
        else
            return node->Size;
    }
public:
    bool empty() { return size() == 0; }
    bool contains(std::string key)
    {
        Node *node = find(key);
        return (node && node->value != Null);
    }
    Node *find(std::string key)
    {
        Node *node = find(root, key, 0);
        if (node == nullptr)
            return nullptr;
        return node;
    }
private:
    Node *find(Node *node, std::string key, int digit)
    {
        if (node == nullptr) return nullptr;
        if (digit == key.size()) return node;

        int nextChar = key[digit];

        Node * pnode = find(node->next[nextChar], key, digit + 1);
        return pnode;
    }
public:
    void put(std::string key, Value v)
    {
        Node *node = find(key);
        if (node != nullptr)
        {
            node->value = v;
            return;
        }
        root = put(root, key, v, 0);
    }
private:
    Node *put(Node *node, std::string key, Value v, int digit)
    {
        if (node == nullptr) node = new Node;
        ++node->Size;
        if (digit == key.size())
        {
            node->value = v;
            return node;
        }

        int nextChar = key[digit];
        node->next[nextChar] = put(node->next[nextChar], key, v, digit + 1);
        return node;
    }
public:
    std::vector<std::string> keys()
    {
        return keysWithPrefix("");
    }
    std::vector<std::string> keysWithPrefix(std::string prefix)
    {
        std::vector<std::string> vs;
        Node *nodePrefix = find(root, prefix, 0);
        collect(nodePrefix, prefix, vs);
        return vs;
    }
private:
    void collect(Node *node, std::string prefix, std::vector<std::string> &vs)
    {
        if (node == nullptr) return;
        if (node->value != Null) vs.push_back(prefix);
        for (char nextChar = 0; nextChar < R; ++nextChar)
        {
            collect(node->next[nextChar], prefix + nextChar, vs);
        }
    }
public:
    std::vector<std::string> keysThatMatch(std::string pattern)
    {
        std::vector<std::string> vs;
        collect(root, std::string(""), pattern, vs);
        return vs;
    }
private:
    void collect(Node *node, std::string prefix, std::string pattern, std::vector<std::string> vs)
    {
        if (node == nullptr) return;
        int sz = prefix.size();
        if (sz == pattern.size() && node->value != Null) vs.push_back(prefix);
        if (sz = pattern.size()) return;

        int nextCharInPattern = pattern[sz];
        for (char nextChar = 0; nextChar < R; ++nextChar)
        {
            if (nextCharInPattern == '.' || nextCharInPattern == nextChar)
                collect(node->next[nextChar], prefix + nextChar, pattern, vs);
        }
    }
public:
    std::string longestPrefixOf(std::string query)
    {
        int length = search(root, query, 0, 0);
        return query.substr(0, length);
    }
private:
    int search(Node *node, std::string query, int digit, int length)
    {
        if (node == nullptr) return length;
        if (node->value != Null) length = digit;

        if (digit == query.size()) return length;

        int nextChar = query[digit];
        return search(node->next[nextChar], query, digit + 1, length);
    }
public:
    void Delete(std::string key)
    {
        if (!contains(key)) return;
        root = Delete(root, key, 0);
    }
private:
    Node *Delete(Node *node, std::string key, int digit)
    {
        if (node == nullptr) return nullptr;
        node->Size = node->Size - 1;
        if (digit == key.size())
            node->value =Null;
        else
        {
            int nextChar = key[digit];
            node->next[nextChar] = Delete(node->next[nextChar], key, digit + 1);
        }

        if (node->value != Null) return node;
        for (int nextChar = 0; nextChar < R; ++nextChar)
            if (node->next[nextChar] != nullptr)
                return node;
        return nullptr;
    }

};

#endif // TRIE_H_
