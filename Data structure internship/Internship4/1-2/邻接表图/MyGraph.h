#pragma once
#include"Graphlnk.h"
#include"MinHeap.h"
#include"MST.h"
template<class T,class E>
class MyGraph:public Graphlnk<T,E>
{
public:
	MyGraph(int sz = DefaultVertices) :Graphlnk<T, E>(sz) {}
	~MyGraph() {};
	void input();
	void output();
	void dfs(const T& v);
	void bfs(const T& v);

	bool CreatByFile(ifstream &in);
	void Prim(MinSpanTree<T, E>& MST);

private:

};

template<class T, class E>
void MyGraph<T, E>::Prim(MinSpanTree<T, E>& MST)
{
	MSTEdgeNode<T, E> ed; //�߽�㸨����Ԫ
	int i, u, v, count;
	int n = this->NumberOfVertices();	  //������	
	int m = this->NumberOfEdges();	  //����
//	int u = getVertexPos(u0);		  //��ʼ�����
	u = 0;
	MinHeap <E, MSTEdgeNode<T, E> > H(m);  //��С��
	bool *Vmst = new bool[n];   //��С���������㼯��
	for (i = 0; i < n; i++) Vmst[i] = false;
	Vmst[u] = true;		        //u ����������
	count = 1;
	do {			        //����	
		v = this->getFirstNeighbor(u);
		while (v != -1) {	 //���u�����ڽӶ���		
			if (!Vmst[v]) {	        //v����mst��			
				ed.tail = u;  ed.head = v;
				ed.key = this->getWeight(u, v);
				H.Insert(ed);	        //(u,v)�����
			}     //���д�����u��mst��, v����mst�еı�
			v = this->getNextNeighbor(u, v);
		}
		while (!H.IsEmpty() && count < n) {
			H.RemoveMin(ed);	         //ѡ���о���СȨ�ı�
			if (!Vmst[ed.head]) {
				MST.Insert(ed);       //������С������
				u = ed.head;
				Vmst[u] = true;//u�������������㼯��
				count++;
				break;
			}
		}
	} while (count < n);
}

template<typename T, typename E>
bool MyGraph<T, E>::CreatByFile(ifstream & in)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight=0;
	in >> n >> m;				//���붥���������
	for (i = 0; i < n; i++) {	//�������붥��ֵ
		in >> e1;
		this->insertVertex(e1);
	}
	i = 0;
	while (i < m) {
		assert(in >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
		j = this->getVertexPos(e1);				//ȡ��Ӧ�����±�
		k = this->getVertexPos(e2);
		if (j == -1 || k == -1) {			//ȡ��Ӧ���㲻����
			cout << "Input error!\n"; return false;
		}
		else {
			this->insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
			i++;
		}
	}
	return true;
}

template<class T, class E>
void MyGraph<T, E>::input() {
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	cin >> n >> m;				//���붥���������
	for (i = 0; i < n; i++) {	//�������붥��ֵ
		cin >> e1;
		this->insertVertex(e1);
	}
	i = 0;
	while (i < m) {
		assert(cin >> e1 >> e2 >> weight);	//��������ߵ�������ֵ����Ȩֵ
		j = getVertexPos(e1);				//ȡ��Ӧ�����±�
		k = getVertexPos(e2);
		if (j == -1 || k == -1) {			//ȡ��Ӧ���㲻����
			cout << "Input error!\n";
		}
		else {
			insertEdge(j, k, weight);		//�ɶ����±��Ȩֵ�����
			i++;
		}
	}
}

template<class T, class E>
void MyGraph<T, E>::output() {
	int i, j, n, m;
	T e1, e2;
	E weight;
	n = this->NumberOfVertices();		//�����������
	m = this->NumberOfEdges();
	cout << "Number of Vertices: " << n << endl;
	cout << "Number of Edges: " << m << endl;
	cout << "The edges in the graph are:\n";
	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			weight = this->getWeight(i, j);
			if (weight > 0 && weight < this->maxWeight) {
				e1 = this->getValue(i);	//���±�ȡ�ö���ֵ
				e2 = this->getValue(j);
				cout << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
			}
		}
	}
}

template<class T, class E>
void MyGraph<T, E>::dfs(const T&v) {//������ȱ���
	bool *visited = new bool[this->numVertices];
	for (int i = 0; i < this->numVertices; i++) {
		visited[i] = false;
	}
	int loc = this->getVertexPos(v);
	cout << this->getValue(loc) << ' ';
	visited[loc] = true;
	stack<int> S; S.push(loc);
	bool sign;
	int w;
	while (!S.empty())
	{
		loc = S.top();
		w = this->getFirstNeighbor(loc);
		sign = false;
		while (w != -1 && sign == false) {
			if (visited[w] == false) {
				cout << this->getValue(w) << " ";
				visited[w] = true;
				sign = true;
				S.push(w);
			}
			w = this->getNextNeighbor(loc, w);
		}
		if (!sign)S.pop();
	}
	delete[] visited;
}

template<class T, class E>
void MyGraph<T, E>::bfs(const T&v) {
	int w;
	bool *visited = new bool[this->numVertices];
	for (int i = 0; i < this->numVertices; i++) {
		visited[i] = false;
	}
	int loc = this->getVertexPos(v);
	cout << this->getValue(loc) << " ";
	visited[loc] = true;
	queue<int> Q; Q.push(loc);
	while (!Q.empty())
	{
		loc = Q.front(); Q.pop();
		w = this->getFirstNeighbor(loc);
		while (w != -1)
		{
			if (visited[w] == false) {
				cout << this->getValue(w) << ' ';
				visited[w] = true;
				Q.push(w);
			}
			w = this->getNextNeighbor(loc, w);
		}
	}
	delete[] visited;
}