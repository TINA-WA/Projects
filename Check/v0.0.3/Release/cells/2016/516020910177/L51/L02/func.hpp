/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{
	int i;
	for(i=2;i<=x;i++)     //循环求因数
	{
		if(x%i==0&&i%2==0)//判断是否为偶因数

		{    
			*(pp+n)=i;  //将偶因数赋值给pp【】
			n++;         //计算因数个数加一
	     }
	}
}