/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{
	* pp=pp[1024];//指针变量pp指向pp数组
	int a=2,i=0;//定义变量
	for(a=2;a<=x;a+=2)
	{
		if(a%2==0&&x%a==0)//如果a是x的偶数因子
			{
				pp[i]=a;//将偶数因子存入数组
				n++;
				i++;
		}
	}
}