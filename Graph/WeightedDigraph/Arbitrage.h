#ifndef ARBITRAGE_H_
#define ARBITRAGE_H_

/** 如果汇率图里有一条路径即：x -> y -> z -> ... -> x
 *  箭头表示兑换，汇率表示权重
 *  若环上所有边权重之积 > 1, 那么就表示套汇机会出现
 *
 *  将边上权重取对数，再取反，问题就等价于找负环
 */


#include "BellmanFordSP.h"
#include <string>

void Arbitrage(std::string filename);
#endif // ARBITRAGE_H_
