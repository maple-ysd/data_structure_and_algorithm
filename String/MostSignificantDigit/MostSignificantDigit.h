#ifndef MOSTSIGNIFICANTDIGIT_H_
#define MOSTSIGNIFICANTDIGIT_H_
/** 高位优先
 *  该算法对有大量重复或公共前缀（长短不一）的字符串（数量超过cutoff = 10的话），该算法复杂度与低位优先相似
 */

#include <string>
#include <vector>

void msdSort(std::vector<std::string> &vs);

#endif // MOSTSIGNIFICANTDIGIT_H_
