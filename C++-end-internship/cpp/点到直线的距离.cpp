// �㵽���ߵľ���.cpp : Defines the entry point for the console application.
/*����㵽���ߵľ��롣
�㵽���ߵľ��붨��Ϊ�㵽������ÿһ���߶εľ����е���̾��룬���㵽�߶εľ����
���ǵ㵽�߶�ĳ���˵�ľ��루�����㲻���߶��ڲ�����Ҳ�����ǵ㵽����ľ��루���������߶�
�ڲ�����Ҫ�������CPoint ��������CLine��������������ʵ�־�������Ա������*/

#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;

class cpoint//����
{
private:
	double x,y;
public:
	cpoint(double xx=0,double yy=0)
	{x=xx;y=yy;}
	double get_x(){return x;}
	double get_y(){return y;}
	void set()
	{
		cout<<"�����������"<<endl;
		cin>>x>>y;
	}
};
class cline//������
{
private:
	cpoint poi;//�������
	double a,b,c;//���ߣ�ax+by+c=0
	double x0,y0;
	double d;
public:
	cline(){}//Ĭ�Ϲ���
	cline(double _a,double _b,double _c)
	{a=_a;b=_b;c=_c;}
	void input()//���뺯��
	{
		poi.set();
		cout<<"��������ϵ��"<<endl;
		cin>>a>>b>>c;}
	void fun()//ֵ����
		{x0=poi.get_x();
		y0=poi.get_y();}
	double fun1()
	{
	double s=fabs(a*x0+b*x0+c);
		double m=sqrt(a*a+b*b);
		d=s/m;
		return d;
	}
	void output() //�������
	{cout<<"�㵽ֱ�߾���Ϊ��"<<d<<endl;}
	~cline(){}//��������
};


int main()
{
	cline c1;
	c1.input();
	c1.fun();
	c1.fun1();
	c1.output();
	::system("pause");
	return 0;
}