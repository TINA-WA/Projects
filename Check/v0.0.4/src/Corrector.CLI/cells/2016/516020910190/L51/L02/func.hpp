/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{
	int i=2;//初始化i=2
	while(i<=x)
	{
		if(x%i==0)
		{	pp[n]=i;//当x能被i整除，储存i
		    n+=1;//计算偶因子的个数
		}
		i=i+2;//保持i一直为偶数
	}
}