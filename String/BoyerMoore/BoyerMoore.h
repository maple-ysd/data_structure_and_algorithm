#ifndef BOYERMOORE_H_
#define BOYERMOORE_H_

/** Boyer-Moore算法，通常情况下~N/M， 最坏情况下O（MN），不过不太可能遇到
 */

#include <vector>
#include <string>

class BoyerMoore
{
public:
    BoyerMoore(std::string pat);
    int search(std::string txt);
private:
    int R = 128;
    std::string pattern;
    std::vector<int> right;

};




#endif // BOYERMOORE_H_
