/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{
	for(int i=2,j=0;i<=x;i++)//用for循环查找因子
	{
		if(x % i== 0 && i % 2 == 0)//判断是否为偶数因子
		{

			*(pp+j)=i;//将偶数因子放入pp所指的数组中
			j++;
			n=n+1;//偶数因子个数
		}
	}
}