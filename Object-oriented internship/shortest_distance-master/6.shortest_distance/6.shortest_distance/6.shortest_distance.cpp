// 6.shortest_distance.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;


int distance(int *num, int n, int center)
{
	int sum = 0;
	for (int i = 1; i<=n; i++) {
		sum += abs(num[i] - center);
	}
	return sum;
}

int main()
{
	fstream myfile("F:\\临时文件\\vs\\6.shortest_distance\\c.txt");
	int x[10000];
	int y[10000];
	int n;
	myfile >> n;
	for (int i = 1; i <= n; i++) {
		myfile >> x[i];
		myfile >> y[i];
	}
	myfile.close();
	sort(x+1, x + n+1);
	int x0 = x[(0 + n/2)];//找到中位数;  
	int dis_x = distance(x, n, x0);//计算每一个x到中位数的距离； 
	sort(y, y + n);
	int y0 = y[(0 + n / 2)];//找到中位数;  
	int dis_y = distance(y, n, y0);//计算每一个x到中位数的距离； 
	myfile.open("F:\\临时文件\\vs\\6.shortest_distance\\d.txt",ios::out);
	int distance_min = dis_x + dis_y;
	myfile << x0 << " " << y0<<'\n';
	myfile << distance_min;
	myfile.close();
		return 0;
}

