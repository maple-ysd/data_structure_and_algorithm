#ifndef ARBITRAGE_H_
#define ARBITRAGE_H_

/** �������ͼ����һ��·������x -> y -> z -> ... -> x
 *  ��ͷ��ʾ�һ������ʱ�ʾȨ��
 *  ���������б�Ȩ��֮�� > 1, ��ô�ͱ�ʾ�׻�������
 *
 *  ������Ȩ��ȡ��������ȡ��������͵ȼ����Ҹ���
 */


#include "BellmanFordSP.h"
#include <string>

void Arbitrage(std::string filename);
#endif // ARBITRAGE_H_
