通常情况下，处理多项式时，链表是个不错的选择

定义一下节点
struct Node
{
double coef;
int expo;
Node *next;
};
typedef Node* Poly;


确定操作
Void Attach(double c, int e, Poly *prear);	// 在一个多项式链表后添加新的项，使用Poly*是因为需要修改rear的值。
void destroy(Poly p);	// 释放多项式链表空间（一连串节点空间）

Poly ReadPoly(istream &is);	// 读取多项式
Poly AddPoly(Poly p1, Poly p2);	// 相加求和并返回
Poly Mult1(Poly p1, Poly p2);		// 借助AddPoly实现， 记得释放每一次新得到的多项式链表，并且释放前一次结果对应的多项式链表
Poly Mult2(Poly p1, Poly p2);		// 先求p1第一项与p2所有相的乘积，然后逐项求解剩余的并插入合适的位置
void Print(Poly p); 			// 打印输出
 

