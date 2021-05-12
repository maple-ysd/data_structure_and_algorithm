#include "Regex.h"
using namespace std;

Regex::Regex(string regularExpressionString)
    : regularExpression(regularExpressionString), digraph(nullptr), numberOfStates(regularExpressionString.size())
{
    digraph = new Digraph(numberOfStates + 1);
    stack<int> operators;
    for (int i = 0; i < numberOfStates; ++i)
    {
        int lp = i;
        if (regularExpression[i] == '(' || regularExpression[i] == '|' || regularExpression[i] == '[')
            operators.push(i);
        else if (regularExpression[i] == ')')
            lp = handleRightParenthesis(operators, i);
        else if (regularExpression[i] == ']')
        {
            lp = operators.top();
            operators.pop();
            handleSets(lp, i);
        }

        if (i < numberOfStates - 1)
        {
            if (regularExpression[i + 1] == '*')
            {
                digraph->addEdge(lp, i + 1);
                digraph->addEdge(i + 1, lp);
            }
            else if (regularExpression[i + 1] == '+')
                digraph->addEdge(i + 1, lp);

        }

        if (regularExpression[i] == '(' || regularExpression[i] == ')' || regularExpression[i] == '['
            || regularExpression[i] == ']' || regularExpression[i] == '*' || regularExpression[i] == '+')
            digraph->addEdge(i, i + 1);
    }
}

int Regex::handleRightParenthesis(stack<int> &operators, int index)
{
    unordered_set<int> orOperatorIndex;
    while (regularExpression[operators.top()] == '|')
    {
        int Or = operators.top();
        operators.pop();
        orOperatorIndex.insert(Or);
    }
    int lp = operators.top();       // 此时必为'('
    operators.pop();
    for (auto i : orOperatorIndex)
    {
        // 处理或运算符与左右括号的连接
        digraph->addEdge(lp, i + 1);
        digraph->addEdge(i, index);
    }
    return lp;
}

void Regex::handleSets(int leftSquareBracket, int index)
{
    bool isComplementSet = false;
    unordered_set<char> charactersToComplement;
    vector<RangeComplement> rangesToComplement;
    // 如果是补集，则先把所有字符放到集合里，然后在recognize里再处理
    if (regularExpression[leftSquareBracket + 1 == '^'])
    {
        isComplementSet = true;
        ++leftSquareBracket;

        for (int i = leftSquareBracket + 1; i < index; ++i)
        {
            if (regularExpression[i + 1] == '-')
            {
                char lp = regularExpression[i];
                char rp = regularExpression[i + 2];
                rangesToComplement.push_back(RangeComplement(lp, rp));
                i += 2;
            }
            else
                charactersToComplement.insert(regularExpression[i]);
        }
    }

    for (int i = leftSquareBracket + 1; i < index; ++i)
    {
        digraph->addEdge(leftSquareBracket, i);
        // 匹配成功的话， 则转到右中括号
        setsMatchMap.insert(make_pair(i, index));
        if (isComplementSet)
        {
            setsComplementMap.insert(make_pair(i, charactersToComplement));
            if (rangesToComplement.size() > 0)
                setsComplementRangesMap.insert(make_pair(i, rangesToComplement));
        }
        // 如果是个范围
        if (regularExpression[i + 1] == '-')
            i += 2;
    }
}

bool Regex::recognize(std::string text)
{
    unordered_set<int> allPossibleStates;     // 初始状态
    DirectedDFS directedDFS(*digraph, 0);
    for (int i = 0; i < digraph->vertices(); ++i)
    {
        if (directedDFS.hasPathTo(i))
            allPossibleStates.insert(i);
    }

    for (int i = 0; i < text.size(); ++i)
    {
        // 为text[i + 1]计算可能的NFA状态
        unordered_set<int> matches;       //
        for (int v : allPossibleStates)
        {
            if (v < numberOfStates)
            {
                if (setsMatchMap.find(v) != setsMatchMap.end())
                    recognizeSet(text, i, v, matches);
                    //
                else if (regularExpression[v] == text[i] || regularExpression[v] == '.')
                    matches.insert(v + 1);
            }
        }
        allPossibleStates.clear();
        DirectedDFS directedDFS2(*digraph, matches);
        for (int v = 0; v < digraph->vertices(); ++v)
            if (directedDFS2.hasPathTo(v))
                allPossibleStates.insert(v);

        // 如果没有可达的状态
        if (allPossibleStates.size() == 0)
             return false;
    }

    for (int v : allPossibleStates)
        if (v == numberOfStates)
            return true;
    return false;
}

void Regex::recognizeSet(string text, int i, int v, unordered_set<int> &matches)
{
    int indexOfRightSquareBracket = setsMatchMap[v];

    // 是否为一个范围
    if (regularExpression[v + 1] == '-')
    {
        char lp = regularExpression[v];
        char rp = regularExpression[v + 2];
        // 文本字符在[x->y]范围内，且不是补集
        if (lp <= text[i] && text[i] <= rp && !isCharPartOfComplementSet(text, i, v))
            matches.insert(indexOfRightSquareBracket);
        // 是补集，但是文本字符不在x->y内
        else if (setsComplementRangesMap.find(v) != setsComplementRangesMap.end() && !isCharPartOfComplementSet(text, i, v))
            matches.insert(indexOfRightSquareBracket);
    }
    //  不是补集，在[xyz........]范围内
    else if (regularExpression[v] == text[i] || regularExpression[v] == '.')
    {
        if (!isCharPartOfComplementSet(text, i, v))
            matches.insert(indexOfRightSquareBracket);
    }
    //  是补集，但是文本字符不在[xyz,,,]范围内
    else if (setsComplementMap.find(v) != setsComplementMap.end() && !isCharPartOfComplementSet(text, i, v))
        matches.insert(indexOfRightSquareBracket);
}

bool Regex::isCharPartOfComplementSet(string text, int i, int v)
{
    if (setsComplementMap.find(v) != setsComplementMap.end() && setsComplementMap[v].find(text[i]) != setsComplementMap[v].end())
        return true;

    if (setsComplementRangesMap.find(v) != setsComplementRangesMap.end())
        for (auto rc : setsComplementRangesMap[v])
            if (rc.leftCharacter <= text[i] && text[i] <= rc.rightCharacter)
                return true;
    return false;
}
