// ����·��.cpp : �������̨Ӧ�ó������ڵ㡣
/*����n-1�����е�������Ѿ����˽������bca���ټ���һ�����С���bcax�����У���������a�Ĳ����Ծ�������x��û��������a�Ŀ��Ծ�������x��Ҳ���Բ���������x���Լ�֮ǰ���г���û������ֻ���˳���x�ġ�
��������x���� f(n-1) - f(n-2) ��
û��������x���� f(n-2) ��
���� f(n) = [f(n-1) - f(n-2)] + [2 * f(n-2)] + 1 = f(n-1) + f(n-2) + 1*/

#include "stdafx.h"
#include<iostream>
using namespace std;

int f(int n)
{
	if(n==0)return 0;
	else if(n==1)return 1;
	else return f(n-1)+f(n-2)+1;
}

int main()
{
	cout<<"�������������"<<endl;
	int n;
	cin>>n;
	if(n>=0){int m=f(n);
	cout<<"·��ѡ���У�"<<m<<"��"<<endl;}
	else cout<<"��������"<<endl;
	::system("pause");
	return 0;
}

