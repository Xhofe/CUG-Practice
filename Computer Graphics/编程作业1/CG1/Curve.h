#pragma once
#include "Spline.h"
using namespace std;
class Curve :
	public Spline
{
public:
	Curve();
	~Curve();

	Curve(int num_vertices);
	
	void Paint(ArgParser *args);
	
	
	void paintBezier(int index,int curve_tessellation);//��һ����index��ʼ��bezier
	void paintBSpline(int index,int curve_tessellation);//��һ����index��ʼ��BSpline

private:

	//float bezierX(float t);
	//float bezierY(float t);
	//float bezierZ(float t);

};

