#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*�����ڽӾ���ʵ��ͼ*/
class GraphAdjMat
{
public:
	vector<int> vertices;       // �����б�Ԫ�ش�������ֵ����������������������
	vector<vector<bool>> adjMat; // �ڽӾ�������������Ӧ������������

	/*���췽��*/
	GraphAdjMat() {}
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
	GraphAdjList(vector<vector<Vertex*>> edge)
	{
		for (vector<Vertex*>& tmp : edge)
		{
			addVertex(tmp[0]);
			addVertex(tmp[1]);
			addEdge(tmp[0], tmp[1]);
		}
	}

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

/*���ڽӱ�Ϊ�����б���*/
/*������ȱ���*/
vector<Vertex*> graphBFS(GraphAdjList& graphList, Vertex* startVertex)
{
	vector<Vertex*> ret = { startVertex };
	unordered_set<Vertex*> visited = { startVertex };// ������¼�ѷ��ʹ��Ķ���
	queue<Vertex*> que;// �����洢��Ҫ���ʵĽڵ�
	que.push(startVertex);
	while (!que.empty())
	{
		for (Vertex* ver : graphList.adjList[que.front()])
		{
			if (visited.find(ver) == visited.end())
			{
				que.push(ver);// ��¼����Ҫ���ʵĶ���
				visited.emplace(ver);// ��¼���ʹ��Ķ���
				ret.emplace_back(ver);// ��¼���ʵ��Ķ���
			}
		}
		que.pop();
	}
	return ret;
}
/*������ȱ���*/
void dfs(GraphAdjList& graph, Vertex* vet, vector<Vertex*>& ret, unordered_set<Vertex*>& visited)
{
	ret.emplace_back(vet);
	visited.emplace(vet);
	for (Vertex* ver : graph.adjList[vet])
	{
		if (visited.find(ver) == visited.end())
		{
			dfs(graph, ver, ret, visited);
		}
	}
}
vector<Vertex*> graphDFS(GraphAdjList& graph, Vertex* startVertex)
{
	vector<Vertex*> ret;// �����������
	unordered_set<Vertex*> visited;// ��¼���ʹ��Ķ���
	// �ݹ��������
	dfs(graph, startVertex, ret, visited);
	return ret;
}

int main()
{
	//vector<int> vertices = { 1,2,3,4,5,6 };
	//vector<vector<bool>> adjMat;/* (6, vector<bool>(6, 0));*/
	////adjMat[1][2] = 1;
	////adjMat[2][1] = 1;

	//GraphAdjMat adj(vertices, adjMat);
	//adj.addEdge(2, 3);
	//adj.print();

	/*vector<Vertex*> v = valsToVets(vector<int>{1, 3, 2, 5, 4});*/

	GraphAdjList adjList;
	Vertex v1(1);
	Vertex v2(2);
	Vertex v3(3);
	Vertex v4(4);
	Vertex v5(5);
	Vertex v6(6);
	Vertex v7(7);
	Vertex v8(8);
	Vertex v9(9);

	adjList.addVertex(&v1);
	adjList.addVertex(&v2);
	adjList.addVertex(&v3);
	adjList.addVertex(&v4);
	adjList.addVertex(&v5);
	adjList.addVertex(&v6);
	adjList.addVertex(&v7);
	adjList.addVertex(&v8);
	adjList.addVertex(&v9);

	adjList.addEdge(&v1, &v2);
	adjList.addEdge(&v1, &v3);
	adjList.addEdge(&v2, &v4);
	adjList.addEdge(&v2, &v5);
	adjList.addEdge(&v3, &v5);
	adjList.addEdge(&v3, &v6);
	adjList.addEdge(&v4, &v7);
	adjList.addEdge(&v5, &v7);
	adjList.addEdge(&v5, &v8);
	adjList.addEdge(&v6, &v8);
	adjList.addEdge(&v7, &v9);
	adjList.addEdge(&v8, &v9);

	adjList.print();
	vector<Vertex*> bfs = graphBFS(adjList, &v1);
	vector<Vertex*> dfs = graphDFS(adjList, &v1);

	adjList.removeEdge(&v2, &v3);
	adjList.removeVertex(&v1);
	

	return 0;
}
