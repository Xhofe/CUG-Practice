// ��Ա��.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <string>
using namespace std;

class Date //�������� 
{
	private: 
		int year; 
		int month; 
		int day; 
	public: Date(){} //Ĭ�Ϲ��� 
			Date(int y,int m,int d) //���ι��� 
			{ year=y; month=m; day=d; } 
			void set() //�������ݺ��� 
			{ cin>>year>>month>>day; } 
			void display() //��ʾ���� 
			{ cout<<year<<"��"<<month<<"��"<<day<<"��"; } }; 
			
class Person //��Ա�� 
{ 
private: 
	int num; 
	char sex; 
	Date birthday; 
	char ID[18]; 
public: Person(){} //Ĭ�Ϲ��� 
		Person(int n,char id[18],char s='m') 
		{ num=n; sex=s; strcpy(ID,id); } //��Ĭ��ֵ�Ĵ��ι��� 
		Person(Person& p) //�������� 
		{ num=p.num; sex=p.sex; birthday=p.birthday; strcpy(ID,p.ID); } 
		void input() //���뺯�� 
		{ cout<<"¼�����ݣ�"<<endl; 
			cout<<"��ţ�"; 
			cin>>num; 
			cout<<"�Ա�(m/w)��"; 
			cin>>sex; cout<<"���գ�"; 
			birthday.set(); 
			cout<<"���֤�ţ�"; 
			cin>>ID; ID[18]='\0'; 
			cout<<endl; } 
		void output() //������� 
			{ cout<<"��ţ�"<<num<<endl; 
			cout<<"�Ա�";
			if(sex='m')
			{cout<<"��"<<endl;} 
			else if(sex='w')
			{cout<<"Ů";}
			else {cout<<"�������";}
			cout<<"���գ�"; birthday.display(); 
			cout<<endl; cout<<"���֤�ţ�"<<ID<<endl; } 
		~Person() //�������� 
		{ cout<<" "<<num<<"����Ա�Ѿ�¼��"<<endl; } }; 
		
int main() 
{ 
	Person p1; 
	p1.input(); 
	p1.output(); 
	::system("pause");
	return 0; 

}

