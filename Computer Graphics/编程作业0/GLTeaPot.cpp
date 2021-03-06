// GLTeaPot.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include<Windows.h>
#include <GL/glut.h>
using namespace std;

/*
* Initialize depth buffer, projection matrix, light source, and lighting
* model.  Do not specify a material property here.
*/

bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraDistanceX;
float cameraDistanceY;
float cameraAngleX;
float cameraAngleY;
float times = 1;
GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };

void init(void)
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//光源位置
	//GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };

	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

GLfloat mat[8][4] = {
	{ 0.2,0.2,0.9 },{ 0.0,0.0,1.0 },{ 1.0,0.0,0.0 },{ 0.0,1.0,0.0 },
{ 0.3,0.3,0.4 },{ 0.1,0.3,0.8 },{ 0.7,0.2,0.5 },{ 0.2,0.8,0.3 }
};
int matIndex = 0;
GLfloat colorMat[] = { 0.2,0.2,0.9 };
void display(void)
{
	//GLfloat mat[4];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScalef(times, times, times);//缩放
	glTranslatef(cameraDistanceX, cameraDistanceY, 0);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	glPushMatrix();
	glTranslatef(8, 8, 0.0);
	//teapot的颜色
	//mat[0] = 0.2; mat[1] = 0.2; mat[2] = 0.9;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, colorMat);

	glutSolidTeapot(3.0);

	glPopMatrix();

	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(0.0, 16.0, 0.0, 16.0 * (GLfloat)h / (GLfloat)w,
			-10.0, 10.0);
	else
		glOrtho(0.0, 16.0 * (GLfloat)w / (GLfloat)h, 0.0, 16.0,
			-10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawScene() {
	if (matIndex == 7)
	{
		matIndex = 0;
	}
	else
	{
		matIndex++;
	}
	GLfloat r = mat[matIndex][0];
	GLfloat g = mat[matIndex][1];
	GLfloat b = mat[matIndex][2];
	GLfloat toR = r - colorMat[0];
	GLfloat toG = g - colorMat[1];
	GLfloat toB = b - colorMat[2];
	int length = max(abs(toR), max(abs(toG), abs(toB))) / 0.01;
	for (size_t i = 0; i < length; i++)
	{
		if (abs(colorMat[0] - r)>0.01)
		{
			colorMat[0] = toR < 0 ? colorMat[0] - 0.01 : colorMat[0] + 0.01;
		}
		if (abs(colorMat[1] - g)>0.01)
		{
			colorMat[1] = toG < 0 ? colorMat[1] - 0.01 : colorMat[1] + 0.01;
		}
		if (abs(colorMat[2] - b)>0.01)
		{
			colorMat[2] = toB < 0 ? colorMat[2] - 0.01 : colorMat[2] + 0.01;
		}
		//cout << colorMat[0] <<' '<< colorMat[1] << ' ' << colorMat[2] << endl;
		//glutPostRedisplay();
		display();
		Sleep(10);
	}

	for (size_t i = 0; i < 3; i++)
	{
		colorMat[i] = mat[matIndex][i];
	}
	glutPostRedisplay();
}

bool isRotate = false;
void rotate(int value) {
	if (isRotate)
	{
		glRotatef(1.0, 1.0, 1.0, 1.0);
		glutPostRedisplay();
	}
	glutTimerFunc(100, rotate, 1);//time,func,id
}

void mouseCB(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	times = 1;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
			mouseLeftDown = false;
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
			mouseRightDown = false;
	}

	/*
	* 鼠标滚轮控制图形缩放
	*/
	else if (state == GLUT_UP && button == 3)
	{
		times = 0.016f + 1;
		glutPostRedisplay();
	}

	else if (state == GLUT_UP && button == 4)
	{
		times = -0.016f + 1;
		glutPostRedisplay();
	}
}

void mouseMotionCB(int x, int y)
{
	cameraAngleX = cameraAngleY = 0;
	cameraDistanceX = cameraDistanceY = 0;

	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX) * 0.3f;
		cameraAngleX += (y - mouseY) * 0.3f;
		mouseX = x;
		mouseY = y;
	}
	if (mouseRightDown)
	{
		cameraDistanceX = (x - mouseX) * 0.002f;
		cameraDistanceY = -(y - mouseY) * 0.002f;
		mouseY = y;
		mouseX = x;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c'://改变颜色
		drawScene();
		break;
	case 'r'://自动旋转
		isRotate = !isRotate;
		break;
	default:
		std::cout << key;
		break;
	}
}
void specialKey(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		position[1] -= 0.5;
		init();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		position[1] += 0.5;
		init();
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		init();
		position[0] -= 0.5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		position[0] += 0.5;
		init();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

/*
* Main Loop
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("hello world");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKey);
	glutTimerFunc(1, rotate, 1);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	glutMainLoop();
	return 0;
}
