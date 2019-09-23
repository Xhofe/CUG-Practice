#pragma once
#include "arg_parser.h"
#include "triangle_mesh.h"
#include <map>
#include <GL/glut.h>
class Spline
{
public:
	Spline();
	~Spline();
	// ���ڻ�ͼ��FOR VISUALIZATION
	virtual void Paint(ArgParser *args);

	// ����ʵ����������ת����FOR CONVERTING BETWEEN SPLINE TYPES
	virtual void OutputBezier(FILE *file);
	virtual void OutputBSpline(FILE *file);

	// ���ڵõ����Ƶ��FOR CONTROL POINT PICKING
	virtual int getNumVertices();
	virtual Vec3f getVertex(int i);

	// ���ڱ༭������FOR EDITING OPERATIONS
	virtual void moveControlPoint(int selectedPoint, float x, float y);
	virtual void addControlPoint(int selectedPoint, float x, float y);
	virtual void deleteControlPoint(int selectedPoint);

	// ���ڲ��������ε�FOR GENERATING TRIANGLES
	virtual TriangleMesh* OutputTriangles(ArgParser *args);
	virtual TriangleMesh* OutputBezierTriangles(ArgParser *args);
	virtual TriangleMesh* OutputBSplineTriangles(ArgParser *args);


	//---------------------------
	Spline(int num_vertices);
	void set(int i, Vec3f v);

	void setFlag(int _flag){ this->flag = _flag; }
	int getFlag() {return flag;}

	void printVertices() {
		printf("-------------------------------\n");
		for (size_t i = 0; i < getNumVertices(); i++)
		{
			printf("%f %f %f\n", getVertex(i).x(), getVertex(i).y(), getVertex(i).z());
		}
		printf("--------------------------------\n");
	}
	void bezierXYZ(float t, float *xyz, int index);
	void bSplineXYZ(float t, float *xyz, int index);

private:
	int num_vertices;
	map<int, Vec3f> vertices;

	int flag;//0->bezier 1->BSpline
};

