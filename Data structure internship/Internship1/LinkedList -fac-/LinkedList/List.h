#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

struct  LinkNode	//������ڵ�
{
	int data;	//������
	LinkNode *link;	//ָ����
	LinkNode(LinkNode *ptr = NULL) { link = ptr; }//����ʼ��ָ��
	LinkNode(const int &item, LinkNode *ptr = NULL) {//��ʼ�����ݺ�ָ��Ĺ���
		data = item; link = ptr;
	}
};

class List	//int��������
{
public:
	List() { first = new LinkNode; };//���캯��
	List(const int &x) { first = new LinkNode(x); }//���캯��
	List(List &L);//���ƹ��캯��
	~List() { makeEmpty(); };//��������
	void makeEmpty();//�ÿ�
	int Length()const;//��ȡ����
	LinkNode *getHead()const { return first; }//��ȡͷ�ڵ�
	LinkNode *Search(int x);//����Ԫ��x
	LinkNode *Locate(int i)const;//��λԪ��
	bool getData(int i, int &x)const;//ȡ��Ԫ�ص�ֵ
	void setData(int i, int &x);//�޸�Ԫ��ֵ
	bool Insert(int i, int &x);//����Ԫ��
	bool Remove(int i, int &x);//�Ƴ�Ԫ��
	bool isEmpty()const//�п�
	{
		return this->first->link == NULL ? true : false;
	}
	bool isFull()const { return false; }//����
	void Sort();
	void Input();
	void Output();//���
	List & operator=(List &L);
	void factorial(int n);
	void Inversion();

protected:
	LinkNode *first;
};

