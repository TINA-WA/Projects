/****************************
 * 寻找数组内偶数的个数
 * 输入 : 数组首地址p
 * 输入 : 数组长度nArraySize
 * 输出 : 偶数的个数n
 ****************************/
void FindEvens(int* p, int nArraySize, int* n)//
{//
	for (int i=0; i<nArraySize; i++)//开始循环
	{//
		if (0 == *(p + i) % 2)//胖丁是否位偶数
			(*n)++;//若是偶数，n加一
	}//
}//