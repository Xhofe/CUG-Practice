// 三羊献瑞.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int main()
{
	int a, b, c, d, e, f, g, h;
	for (a = 0; a <= 9; a++)//多重循环
		for (b = 0; b <= 9; b++)
			for (c = 0; c <= 9; c++)
				for (d = 0; d <= 9; d++)
					for (e = 1; e <= 9; e++)
						for (f = 0; f <= 9; f++)
							for (g = 0; g <= 9; g++)
								for (h = 0; h <= 9; h++)
									if (a * 1000 + b * 100 + c * 10 + d + e * 1000 + f * 100 + g * 10 + b == e * 10000 + f * 1000 + c * 100 + b * 10 + h&&a != b && a != c && a != d && a != e&&a != f && a != g && a != h
										&& b != c && b != d && b != e&&b != f && b != g &&b != h
										&& c != d && c != e&&c != f && c != g && c != h
										&& d != e&&d != f && d != g &&d != h
										&& f != g && f != h
										&& g != h
										&& a != 1 && b != 1 && c != 1 && d != 1 && f != 1 && g != 1 && h != 1 && e == 1)//条件控制

										cout << "三="<<e << '\t' << "羊=" << f << '\t' << "献=" << g << '\t' << "瑞=" << b << endl;//输出结果
	::system("pause");//暂停
	return 0;
}

