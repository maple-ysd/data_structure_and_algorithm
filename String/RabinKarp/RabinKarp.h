#ifndef RABINKARP_H_
#define RABINKARP_H_

#include <string>

class RabinKarp
{
public:
    RabinKarp(std::string pat);
    int search(std::string txt);
private:
    long hash(std::string str, int K);
    std::string pattern;
    long patHash;       // 模式串的散列值
    int M;              // 模式串长度
    long Q = 2147483647;    // 一个很大的素数, 若每一次能有不同的Q则可以重复实验验证（不验证也可以，数很大的情况下）
                            // 或者（质数比较小的情况下）对比找到的子串与模式串挨个比较（主要是考虑到哈希冲突）
    int R = 128;              // 字母表大小
    long RM;            // R^(M-1) % Q， 用于减去第一位字符
};

#endif // RABINKARP_H_
