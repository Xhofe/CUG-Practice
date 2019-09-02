#pragma once
#include "LinkedQueue.h"
class TrainScheduling
{
public:
	TrainScheduling(int train[], int len, int rail);
	~TrainScheduling();
	bool Scheduling();

private:
	LinkedQueue<int> *p_rail;//��������
	int *p_train;//����
	int len;//�𳵸���
	int rail;//�������
};

TrainScheduling::TrainScheduling(int train[],int len, int rail)
{
	this->len = len;
	this->rail = rail;
	p_rail = new LinkedQueue<int>[this->rail];
	p_train = new int[this->len];
	for (int i = 0; i < this->len; i++)
	{
		this->p_train[i] = train[i];
	}
}

TrainScheduling::~TrainScheduling()
{
	delete[] p_rail;
	delete[] p_train;
}

bool TrainScheduling::Scheduling()
{
	int out = 1;//��ǰӦ�ó��еĳ�
	int i = len - 1;//����ĳ�
	int NonEmptyRail=0;//��¼�ǿ���������
	while (out<=len)
	{
		//cout << "Non" << NonEmptyRail << endl;
		//cout << i << p_train[i] << out << NonEmptyRail << rail << endl;
		if (i >= 0 && p_train[i] == out&&NonEmptyRail<rail) {
			cout << out << "��" <<  rail << "�������"<<endl;
			i--; out++;
			continue;
		}
		else{
			int temp = 0;//��¼�Ƿ����������ҵ������
			for (int j = 0; j < rail; j++) {
				if (!p_rail[j].isEmpty()) {
					if (p_rail[j].getFront() == out) {
						cout << out << "��" << j+1 << "�������" <<endl;
						p_rail[j].Dequeue();
						if (p_rail[j].isEmpty()) { NonEmptyRail--; }
						out++;
						temp++;
					}
				}
				if (temp > 0)break;
			}
			if (temp > 0)continue;
			else
			{
				int max = 0;
				int t_rail = -1;
				for (int j = 0; j < rail; j++) {
					if (!p_rail[j].isEmpty()) {
						//cout << p_rail[j].getRear() << p_train[i] << p_rail[j].getRear() << max << endl;
						if (p_rail[j].getRear() < p_train[i]&&p_rail[j].getRear() > max) {
							//cout << "����ǿն���" << endl;
							t_rail = j;
							max = p_rail[j].getRear();
						}
					}
				}
				if (max != 0) {
					p_rail[t_rail].EnQueue(p_train[i]);
					cout << p_train[i] << "����" << t_rail+1 << "���" << endl;
					i--;
					continue;
				}
				else if(NonEmptyRail<rail)
				{
					for (int j = 0; j < rail; j++) {
						if (p_rail[j].isEmpty()) {
							p_rail[j].EnQueue(p_train[i]);
							cout << p_train[i] << "����" << j+1 << "���" << endl;
							i--;
							NonEmptyRail++;
							break;
						}
					}
				}
				else
				{
					cout << "ʧ��" << endl;
					return false;
				}
			}
		}
	}
	cout << "�ɹ�" << endl;
	return true;
}
