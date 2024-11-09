#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*�����ڽӾ���ʵ��ͼ*/
class GraphAdjMat
{
public:
	vector<int> vertices;       // �����б�Ԫ�ش�������ֵ����������������������
	vector<vector<bool>> adjMat; // �ڽӾ�������������Ӧ������������

	GraphAdjMat(vector<int>& vet, vector<vector<bool>>& edges)
	{
		// ��Ӷ���
		for (int val : vet)
			addVertex(val);
	}

	/*��ȡ�ڵ����*/
	int size()
	{
		return vertices.size();
	}

	/*��Ӷ���*/
	void addVertex(int val)
	{
		int n = size();
		// ��ӽڵ�
		vertices.emplace_back(val);
		// �����
		adjMat.emplace_back(vector<bool>(n, 0));
		// �����
		for (vector<bool>& tmp : adjMat)
			tmp.emplace_back(0);
	}
	/*ɾ������*/
	void removeVertex(int index)
	{
		if (index < 0 || index >= size())
		{
			cout << "�ڵ㲻����" << endl;
			return;
		}
		// ɾ����Ӧ����
		vertices.erase(vertices.begin() + index);
		// ɾ����
		adjMat.erase(adjMat.begin() + index);
		// ɾ����
		for (vector<bool>& row : adjMat)
			row.erase(row.begin() + index);
	}
	/*��ӱ�*/
	void addEdge(int i, int j)
	{
		if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
		{
			//throw out_of_range("���㲻����");
			cout << "���㲻����" << endl;
			return;
		}
		// ������ͼ�У��ڽӾ���������Խ��߶Գƣ������� (i, j) == (j, i)
		adjMat[i][j] = 1;
		adjMat[j][i] = 1;
	}
	/*ɾ����*/
	void removeEdge(int i, int j)
	{
		if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
		{
			cout << "���㲻����" << endl;
			return;
		}
		adjMat[i][j] = 0;
		adjMat[j][i] = 0;
	}
	/*��ӡ*/
	void print()
	{
		// ��ӡ����
		cout << "   ";
		for (int val : vertices)
			cout << val << "  ";
		cout << '\n';
		// ��ӡ�ڽӾ���
		for (int i = 0; i < size(); ++i)
		{
			vector<bool>& row = adjMat[i];
			cout << vertices[i] << "  ";
			for (int j = 0; j < row.size(); ++j)
				cout << row[j] << "  ";
			cout << '\n';
		}
	}
};

/*�ڽӱ�*/
struct Vertex
{
	// Vertex��ʾ���㣬�ṹ���ڰ��贴���������˴���int���;���
	int k;
	// ���췽��
	Vertex(int x = 0) :k(x) {}
};
class GraphAdjList
{
private:
	/*�� vector ��ɾ��ָ������*/
	void remove(vector<Vertex*>& vertex, Vertex* vet)
	{
		for (int i = 0; i < vertex.size(); ++i)
			if (vertex[i] == vet)
			{
				vertex.erase(vertex.begin() + i);
				break;
			}
	}

public:
	// key�����㣬value���ö���������ڽӱ�
	unordered_map<Vertex*, vector<Vertex*>> adjList;

	/*���췽��*/
	GraphAdjList() {}

	/*��ȡ��������*/
	int size()
	{
		return adjList.size();
	}

	/*��Ӷ���*/
	void addVertex(Vertex* vet)
	{
		if (adjList.count(vet))
			return;
		adjList[vet] = vector<Vertex*>();
	}

	/*ɾ������*/
	void removeVertex(Vertex* vet)
	{
		if(!adjList.count(vet))
			throw invalid_argument("�����ڶ���");
		adjList.erase(vet);
		// �����������㣬ɾ������ vet �ı�
		for (auto& vertex : adjList)
			remove(vertex.second, vet);
	}

	/*��ӱ�*/
	void addEdge(Vertex* vet1, Vertex* vet2)
	{
		if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
			throw invalid_argument("�����ڶ���");
		adjList[vet1].push_back(vet2);
		adjList[vet2].push_back(vet1);
	}

	/*ɾ����*/
	void removeEdge(Vertex* vet1, Vertex* vet2)
	{
		if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
			throw invalid_argument("�����ڶ���");
		remove(adjList[vet1], vet2);
		remove(adjList[vet2], vet1);
	}

	/*��ӡ*/
	void print()
	{
		for (auto& vertex : adjList)
		{
			cout << vertex.first->k << ": ";
			for (int i = 0; i < vertex.second.size(); ++i)
				cout << vertex.second[i]->k << "  ";
			cout << '\n';
		}
	}
};

int main()
{
	vector<int> vertices = { 1,2,3,4,5,6 };
	vector<vector<bool>> adjMat;/* (6, vector<bool>(6, 0));*/
	//adjMat[1][2] = 1;
	//adjMat[2][1] = 1;

	GraphAdjMat adj(vertices, adjMat);
	adj.addEdge(2, 3);
	adj.print();

	GraphAdjList adjList;
	Vertex v1(1);
	Vertex v2(2);
	Vertex v3(3);
	adjList.addVertex(&v1);
	adjList.addVertex(&v2);
	adjList.addVertex(&v3);

	adjList.addEdge(&v1, &v2);
	adjList.addEdge(&v1, &v3);
	adjList.addEdge(&v2, &v3);

	adjList.print();

	adjList.removeEdge(&v2, &v3);
	adjList.removeVertex(&v1);
	

	return 0;
}
