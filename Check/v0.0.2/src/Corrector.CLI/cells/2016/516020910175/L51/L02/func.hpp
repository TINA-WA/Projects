/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func05(int x, int* pp, int& n)
{
	x=x>0?x:-x;//对x取绝对值
	int i;//定义循环变量
	n=0;//赋个数n的初值
	for(i=2;i<=x;i+=2)//对小于|x|的偶数逐个判断
	{
		if(x%i==0) *(pp+n++)=i;//如果是因数则存放并使n加一
	}
}