#include <iostream>
#include <vector>
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

int main()
{
	vector<int> vertices = { 1,2,3,4,5,6 };
	vector<vector<bool>> adjMat;/* (6, vector<bool>(6, 0));*/
	//adjMat[1][2] = 1;
	//adjMat[2][1] = 1;

	GraphAdjMat adj(vertices, adjMat);
	adj.addEdge(2, 3);
	adj.print();

	return 0;
}
