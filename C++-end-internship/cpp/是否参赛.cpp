// 是否参赛.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include<iostream>
using namespace std;
char *f(int n)//f函数将“0”和“1”还原成“不参加”和“参加”
{
	if (n == 0)	return "不参加";
	if (n == 1)	return "参加";
}
int main()
{
	int a, b, c, d, e;
	for (a = 0; a <= 1;a++)//多重循环
		for (b = 0; b <= 1; b++)
			for (c = 0; c <= 1; c++)
				for (d = 0; d <= 1; d++)
					for (e = 0; e <= 1; e++)
				{	if (a&&!b)	
						continue;
					if (b==c)	
						continue;
					if (c!=d)	
						continue;
					if (!d&&!e)	
						continue;
					if (e && (!a || !d))	
						continue;//条件控制
					cout << 'A' << f(a)<<'\n'<< 'B' << f(b) << '\n' << 'C' << f(c) << '\n' << 'D' << f(d) << '\n' << 'E' << f(d)  << endl;//输出结果调用f函数
				}
				::system("pause");
	return 0;
}

