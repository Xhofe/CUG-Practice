#pragma once
#include<list>
#include<cmath>
#include"cocos2d.h"
#include"Result.h"
USING_NS_CC;


struct AStarNode
{
	int f;//�������ֵ
	int g;//�õ㵽���ľ���
	int h;//�õ㵽�յ�Ĺ���ֵ
	AStarNode *parent;//ǰ����
	int x;
	int y;
	int xend, yend;
	//bool isVisit;
	AStarNode(int _x, int _y, int _xend, int _yend, AStarNode *ptr = NULL) :x(_x), y(_y),xend(_xend),yend(_yend), parent(ptr) {
		if (ptr != NULL) { g = parent->g + 1; }
		else{
			g = 0;
		}
		h = abs(x - xend) + abs(y - yend);
		f = g + h;
		//isVisit = false;
	}
};

class AStar
{
public:
	AStar(int **newmap, int x1, int y1, int x2, int y2);
	bool FindPath();
	~AStar();
	std::stack<Point*> getPath();

private:
	int map[28][38];
	std::list<AStarNode*> OpenList;
	//std::list<AStarNode*> ClosedList;
	bool isEnd;
	AStarNode *minNode();
	AStarNode *isContain(int x, int y);
	std::stack<Point*> Path;
};