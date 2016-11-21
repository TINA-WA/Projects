/****************************
 * 寻找数组内偶数的个数
 * 输入 : 数组首地址p
 * 输入 : 数组长度nArraySize
 * 输出 : 偶数的个数n
 ****************************/
void FindEvens(int* p, int nArraySize, int* n)
{
	*n = 0;//初始化偶数值
	for (int i = 0; i < nArraySize; i++)//开始找偶数的个数
	{
		if (*(p + i) %2== 0)        //判断是否为偶数
		{
			*n = *n + 1;             //偶数个数加一
		}
	}
}