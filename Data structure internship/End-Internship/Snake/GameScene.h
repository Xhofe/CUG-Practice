#pragma once
#include"cocos2d.h"
#include"HelloWorldScene.h"
#include"time.h"
#include"stdlib.h"
#include"AStar.h"
#include<fstream>
#include"SimpleAudioEngine.h"
#include"Result.h"

USING_NS_CC;
class MyResult;

enum DIR {
	up=28,down=29,right=27,left=26
};

class SnakeNode :public cocos2d::Sprite{
public:
	static SnakeNode* create(const std::string &fileName) {
		SnakeNode * sprite = new SnakeNode();
		if (sprite&& sprite->initWithFile(fileName))
		{
			sprite->autorelease(); return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	SnakeNode* pre;
	SnakeNode(SnakeNode *ptr = NULL) {
		this->pre = ptr;
	}
};

class GameScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	virtual void myupdate(float dt);
	virtual void automatic(float dt);
	// implement the "static create()" method manually
	void CreatFood();
	//���̼���
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event*event);
	CREATE_FUNC(GameScene);
	void move();
	void EatFood();
	bool ReadWord();
	void searchPath();
	void ResetMap();
	bool EatSelf();//���Ե��Լ�
	bool IsOut();//����Ƿ���߿�

	static int sceneNum;
protected:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float contentScaleFactor;
	DIR dir;//��ͷ�ķ���
	

	SnakeNode *head;
	cocos2d::Sprite *food;//ʳ��
	cocos2d::Label *des;//��������
	cocos2d::Label *ShowWord;//��ʾ�ĵ���
	cocos2d::Label *Score;//����
	cocos2d::Label *Live;//����
	cocos2d::Label *SpeedLB;//�ٶ���ʾ
	
	std::stack<Point*> Path;
	std::vector<SnakeNode*> SnakeBody;
	std::list<cocos2d::Sprite*> SnakeFood;//ʳ��

	std::ifstream fin;//�ļ���
	std::string word;//��ǰ����
	std::string description;//��������
	std::string showstr;//��ʾ�ĵ���
	std::string score_str;
	std::string live_str;

	int n;//�ߵĳ���
	int current;//��ǰ���ʵĵڼ�����ĸ
	int **map;//��ǰ��Ϸ��״̬ 0��ʾ·��1��ʾ��㣬2��ʾ�ϰ���3��ʾ�յ�
	int live;//������
	int score;//����
	float speed;//�ٶ�
	float autoSpeed;//�Զ�Ѱ·�ٶ�
	bool isPlay;//�����Ƿ��ڲ���
	int SpeedLevel;//0����1�У�2��

	MyResult *p_Res;//�޸���Ϸ��������
};

