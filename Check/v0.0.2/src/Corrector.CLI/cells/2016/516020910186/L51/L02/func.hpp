/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{
	if(x%2==0)//如果x为偶数
	{
		for(int i=2;i<=x;i=i+2)//用循环找到偶数因子
		{
			if(x%i==0)//判断是否能整除
			{
				pp[n]=i;//加入数组
				n=n+1;//个数加1
			}
		}
	}
	else n=0;//若为奇数
}