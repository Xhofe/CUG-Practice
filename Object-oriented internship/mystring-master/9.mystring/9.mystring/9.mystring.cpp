// 9.mystring.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <malloc.h>
using namespace std;

class mystr
{
private:

	int length;//字符串长度
	int size;//字符串类的容量
public:
	char *mstr;
	mystr() {
		this->length = 0;
		this->size = 10;
		this->mstr = (char*)malloc(size);
		for (int i = 0; i < size; i++) {
			this->mstr[i] = 0;
		}
	}
	~mystr()
	{
		free(mstr);
	}
	void assign(const char *astr)
	{
		while (strlen(astr) > size) { size = size * 2; }
		int i = 0;
		while (astr[i])
		{
			mstr[i] = astr[i++];
			length++;
		}
	}
	int GetLength() {
		return length;
	}
	bool IsEmpty() {
		if (length == 0) { return false; }
		else return true;
	}
	int GetAt(const char ch) {
		for (int i = 0; i < length; i++)
		{
			if (this->mstr[i] == ch)
				return i;
		}
		return -1;//未找到
	}
	mystr &operator+(mystr&that) {
		mystr sumstr;
		sumstr.length = this->length + that.length;
		while (sumstr.length>sumstr.size)
		{
			sumstr.size = sumstr.size * 2;
		}
		int i = 0;
		while (this->mstr[i])
		{
			sumstr.mstr[i] = this->mstr[i++];
		}
		i = 0;
		while (that.mstr[i])
		{
			sumstr.mstr[i+this->length] = that.mstr[i++];
		}
		*this = sumstr;
		return *this;
	}
	mystr &operator=(mystr&that)
	{
		if (this == &that)
			return *this;
		this->length = that.length;
		this->size = that.size;
		free(mstr);
		mstr = (char*)malloc(size);
		int i = 0;
		while (i<size)
		{
			this->mstr[i] = that.mstr[i++];
		}
		return *this;
	}
	void Insert(const char* istr, int i)//插入的字符(串)和位置
	{
		while (strlen(istr) + this->length>this->size)
		{
			size = size * 2;
		}
		this->length = this->length + strlen(istr);
		/*for (int k = i + strlen(istr); k < this->length; k++)
		{
			this->mstr[k] = this->mstr[k - strlen(istr)];
		}*/
		for (int j = length; j>i; j--)
		{
			this->mstr[j] = this->mstr[j - strlen(istr)];
		}
		for (int j = 0; j < strlen(istr); j++)
			this->mstr[i++] = istr[j];
	}
	void Delete(const char *dstr)
	{
		this->length = this->length - strlen(dstr);
		int i = GetAt(dstr[0]);
		for (i; i < length; i++)
		{
			this->mstr[i] = this->mstr[i + strlen(dstr)];
		}
		int j = length;
		int k = 0;
		while (dstr[k++])
		{
			//mstr[j] = mstr[j+strlen(dstr)];
			mstr[j ++ ] = 0;
		}
	}
	void Replace(const char *ch1,const char *ch2)
	{
		int n = GetAt(ch1[0]);
		Delete(ch1);
		Insert(ch2, n);
	}



};

int main()
{

	mystr str1;
	str1.assign("aaaa");
	cout << str1.GetLength() << endl;
	cout << str1.IsEmpty() << endl;
	mystr str2;
	str2.assign("bbbb");
	mystr str3;
	str3.assign("a");
	str3 = str1 + str2;
	cout << str3.mstr << endl;
	str3.Insert("cccc", 4);
	cout << str3.mstr << endl;
	str3.Delete("cccc");
	cout << str3.mstr << endl;
	str3.Replace("aaaa", "dddd");
	cout << str3.mstr << endl;
	::system("pause");
	return 0;
}

