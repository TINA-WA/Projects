/***************************************
 * 求出x的偶数因子
 * 并按从小到大的顺序放在pp所指的数组中
 * 输入 : 整数x
 * 输出 : 偶数因子数组pp
 * 输出 : 因子个数n
 ***************************************/
void func(int x, int* pp, int& n)
{for(int i=1;i<=x;i++)
{if(x%i==0&&i%2==0)  //判断i是否为x的偶数因子
{ n+=1;      //对pp数组进行处理
 *pp=i;
 pp+=1;}
}	
}