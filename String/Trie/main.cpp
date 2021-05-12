#include <iostream>
#include "Trie.h"
using namespace std;

int main()
{
    Trie<int> trie;
    trie.put("a", 1);
    trie.put("b", 2);
    trie.put("hello", 3);
    trie.put("good", 4);
    trie.Delete("a");
    cout << trie.size() << endl;
    return 0;
}
