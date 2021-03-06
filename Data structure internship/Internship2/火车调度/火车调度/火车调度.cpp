// 火车调度.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "TrainScheduling.h"
using namespace std;

int main()
{
	//测试数据：
	//N=20, K=3，{3,4,6,1,11,13,5,7,19,8,12,2,9,16,10,14,17,18,20,15}
	//N=9，K=3，{5,8,1,7,4,2,9,6,3}
	while (1)
	{
		cout << "输入火车数量（输入0退出）：" << endl;
		int n, m;
		cin >> n;
		if (n == 0)break;
		int *array = new int[n];
		cout << "输入" << n << "个数代表火车：" << endl;
		for (int i = 0; i < n; i++) {
			cin >> array[i];
		}
		cout << "输入铁轨数：" << endl;
		cin >> m;
		TrainScheduling *p = new TrainScheduling(array, n, m);
		p->Scheduling();
		delete p;
	}
	return 0;
}
