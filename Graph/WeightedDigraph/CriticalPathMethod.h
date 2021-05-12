#ifndef CRITICALPATHMETHOD_H_
#define CRITICALPATHMETHOD_H_
#include <string>

/** 任务调度的关键路径 <-> 最长路径问题
 *  即拓扑排序->按拓扑顺序松弛（与最短路径时符号相反）每一个顶点。
 */


void CriticalPathMethod(std::string filename);

#endif // CRITICALPATHMETHOD_H_
