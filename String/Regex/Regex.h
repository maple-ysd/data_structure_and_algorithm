#ifndef REGEX_H_
#define REGEX_H_

/** 正则表达式字符串匹配
 *  O（MN）
 */

#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include "../../Graph/Digraph/Digraph.h"
#include "../../Graph/Digraph/DirectedDFS.h"


class Regex
{
    struct RangeComplement
    {
        char leftCharacter;
        char rightCharacter;
        RangeComplement(char lc, char rc): leftCharacter(lc), rightCharacter(rc) {}
    };
public:
    Regex(std::string regularExpressionString);
    ~Regex() { delete digraph; }
    bool recognize(std::string text);
private:
    int handleRightParenthesis(std::stack<int> &operators, int index);
    void handleSets(int leftSquareBracket, int index);
    void recognizeSet(std::string text, int index, int vex, std::unordered_set<int> &states);
    bool isCharPartOfComplementSet(std::string text, int index, int vex);
    std::string regularExpression;
    Digraph *digraph;           // Epsilon transitions(空转换)
    int numberOfStates;
    std::unordered_map<int, int> setsMatchMap;
    std::unordered_map<int, std::unordered_set<char>> setsComplementMap;
    std::unordered_map<int, std::vector<RangeComplement>> setsComplementRangesMap;
};
#endif // REGEX_H_
