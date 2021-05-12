#ifndef TEXTEDITORBUFFER_H_
#define TEXTEDITORBUFFER_H_

#include <iostream>

class TextEditorBuffer
{
    struct Node
    {
        char data;
        Node *next;
    };
public:
    TextEditorBuffer() {}
    ~TextEditorBuffer();
    int size() { return leftSize + rightSize; }
    void insert(char c);
    char Delete();
    void left(int k);
    void right(int k);
private:
    int leftSize = 0;
    int rightSize = 0;
    Node *leftStack = nullptr;
    Node *rightStack = nullptr;
};

TextEditorBuffer::~TextEditorBuffer()
{
    if (leftSize > 0)
    {
        for (int i = 0; i < leftSize; ++i)
        {
            Node *temp = leftStack;
            leftStack = leftStack->next;
            delete temp;
        }
    }
    if (rightSize > 0)
    {
        for (int i = 0; i < rightSize; ++i)
        {
            Node *temp = rightStack;
            rightStack = rightStack->next;
            delete temp;
        }
    }
}
void TextEditorBuffer::insert(char c)
{
    Node *pnew = new Node;
    if (!pnew)
    {
        std::cout << "memory allocation in insert operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    pnew->data = c;
    pnew->next = leftStack;
    ++leftSize;
    leftStack = pnew;
}
char TextEditorBuffer::Delete()
{
    if (leftSize == 0)
    {
        std::cout << "buffer is empty, Delete operation failed.\n";
        std::exit(EXIT_FAILURE);
    }
    char ch = leftStack->data;
    Node *temp = leftStack;
    leftStack = leftStack->next;
    delete temp;
    --leftSize;
    return ch;
}

void TextEditorBuffer::left(int k)
{
    for (int i = 0; i < k && leftSize > 0; ++i)
    {
        // delete from leftStack and store the data
        char ch = leftStack->data;
        Node *temp = leftStack;
        leftStack = leftStack->next;
        delete temp;
        --leftSize;
        // insert the data to rightStack
        Node *pnew = new Node;
        if (!pnew)
        {
            std::cout << "memory allocation in left operation failed.\n";
            std::exit(EXIT_FAILURE);
        }
        pnew->data = ch;
        pnew->next = rightStack;
        rightStack = pnew;
        ++rightSize;
    }   // here the process is realized in a normal way, but we can directly change the link without delete and new another node
}

void TextEditorBuffer::right(int k)
{
    for (int i = 0; i < k && rightSize > 0; ++i)
    {
        // delete from rightStack and store the data
        char ch = rightStack->data;
        Node *temp = rightStack;
        rightStack = rightStack->next;
        delete temp;
        --rightSize;

        // insert the data to leftStack
        insert(ch);
    }
}
#endif // TEXTEDITORBUFFER_H_
