/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{
	int YIN[1024];
	int m = -1;
	for (int i = 1; i <= x; i++)
	{
		if (x%i == 0)
		{
			m++;
			YIN[m] = i;
		}
	}                                                    //寻找x的因子
	for (int j = 0; j <= m; j++)
	{
		if (YIN[j] % 2 == 0)                             //判断x的因子是否是偶数
		{
			pp[n] = YIN[j];
			n++;
		}
	}
}