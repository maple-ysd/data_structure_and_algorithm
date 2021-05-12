#ifndef KMP_H_
#define KMP_H_

#include <vector>
#include <string>

class KMP
{
public:
    KMP(std::string pat);
    int search(std::string txt);
private:
    int R = 128;
    std::string pattern;
    std::vector<std::vector<int>> dfa;
};

#endif // KMP_H_
