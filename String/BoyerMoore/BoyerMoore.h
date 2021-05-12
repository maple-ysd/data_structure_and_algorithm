#ifndef BOYERMOORE_H_
#define BOYERMOORE_H_

/** Boyer-Moore�㷨��ͨ�������~N/M�� ������O��MN����������̫��������
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
