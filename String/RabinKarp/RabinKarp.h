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
    long patHash;       // ģʽ����ɢ��ֵ
    int M;              // ģʽ������
    long Q = 2147483647;    // һ���ܴ������, ��ÿһ�����в�ͬ��Q������ظ�ʵ����֤������֤Ҳ���ԣ����ܴ������£�
                            // ���ߣ������Ƚ�С������£��Ա��ҵ����Ӵ���ģʽ�������Ƚϣ���Ҫ�ǿ��ǵ���ϣ��ͻ��
    int R = 128;              // ��ĸ���С
    long RM;            // R^(M-1) % Q�� ���ڼ�ȥ��һλ�ַ�
};

#endif // RABINKARP_H_
