#ifndef LEASTSIGNIFICANTDIGIT_H_
#define LEASTSIGNIFICANTDIGIT_H_
/** 低位字符串优先排序
 *  O(n * w)， n字符串个数， w字符串长度
 *  要求字符串定长
 */

#include <string>
#include <vector>
// n表示待排序字符串的宽带
void lsdSort(std::vector<std::string> &arr, int n);


#endif // LEASTSIGNIFICANTDIGIT_H_
