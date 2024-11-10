#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*基于邻接矩阵实现图*/
class GraphAdjMat
{
public:
	vector<int> vertices;       // 顶点列表，元素代表“顶点值”，索引代表“顶点索引”
	vector<vector<bool>> adjMat; // 邻接矩阵，行列索引对应“顶点索引”

	/*构造方法*/
	GraphAdjMat() {}
	GraphAdjMat(vector<int>& vet, vector<vector<bool>>& edges)
	{
		// 添加顶点
		for (int val : vet)
			addVertex(val);
	}

	/*获取节点个数*/
	int size()
	{
		return vertices.size();
	}

	/*添加顶点*/
	void addVertex(int val)
	{
		int n = size();
		// 添加节点
		vertices.emplace_back(val);
		// 添加行
		adjMat.emplace_back(vector<bool>(n, 0));
		// 添加列
		for (vector<bool>& tmp : adjMat)
			tmp.emplace_back(0);
	}
	/*删除顶点*/
	void removeVertex(int index)
	{
		if (index < 0 || index >= size())
		{
			cout << "节点不存在" << endl;
			return;
		}
		// 删除对应顶点
		vertices.erase(vertices.begin() + index);
		// 删除行
		adjMat.erase(adjMat.begin() + index);
		// 删除列
		for (vector<bool>& row : adjMat)
			row.erase(row.begin() + index);
	}
	/*添加边*/
	void addEdge(int i, int j)
	{
		if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
		{
			//throw out_of_range("顶点不存在");
			cout << "顶点不存在" << endl;
			return;
		}
		// 在无向图中，邻接矩阵关于主对角线对称，即满足 (i, j) == (j, i)
		adjMat[i][j] = 1;
		adjMat[j][i] = 1;
	}
	/*删除边*/
	void removeEdge(int i, int j)
	{
		if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
		{
			cout << "顶点不存在" << endl;
			return;
		}
		adjMat[i][j] = 0;
		adjMat[j][i] = 0;
	}
	/*打印*/
	void print()
	{
		// 打印顶点
		cout << "   ";
		for (int val : vertices)
			cout << val << "  ";
		cout << '\n';
		// 打印邻接矩阵
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

/*邻接表*/
struct Vertex
{
	// Vertex表示顶点，结构体内按需创建变量，此处以int类型举例
	int k;
	// 构造方法
	Vertex(int x = 0) :k(x) {}
};
class GraphAdjList
{
private:
	/*在 vector 中删除指定顶点*/
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
	// key：顶点，value：该顶点的所有邻接边
	unordered_map<Vertex*, vector<Vertex*>> adjList;

	/*构造方法*/
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

	/*获取顶点数量*/
	int size()
	{
		return adjList.size();
	}

	/*添加顶点*/
	void addVertex(Vertex* vet)
	{
		if (adjList.count(vet))
			return;
		adjList[vet] = vector<Vertex*>();
	}

	/*删除顶点*/
	void removeVertex(Vertex* vet)
	{
		if(!adjList.count(vet))
			throw invalid_argument("不存在顶点");
		adjList.erase(vet);
		// 遍历其他顶点，删除包含 vet 的边
		for (auto& vertex : adjList)
			remove(vertex.second, vet);
	}

	/*添加边*/
	void addEdge(Vertex* vet1, Vertex* vet2)
	{
		if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
			throw invalid_argument("不存在顶点");
		adjList[vet1].push_back(vet2);
		adjList[vet2].push_back(vet1);
	}

	/*删除边*/
	void removeEdge(Vertex* vet1, Vertex* vet2)
	{
		if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
			throw invalid_argument("不存在顶点");
		remove(adjList[vet1], vet2);
		remove(adjList[vet2], vet1);
	}

	/*打印*/
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

/*以邻接表为例进行遍历*/
/*广度优先遍历*/
vector<Vertex*> graphBFS(GraphAdjList& graphList, Vertex* startVertex)
{
	vector<Vertex*> ret = { startVertex };
	unordered_set<Vertex*> visited = { startVertex };// 用来记录已访问过的顶点
	queue<Vertex*> que;// 用来存储需要访问的节点
	que.push(startVertex);
	while (!que.empty())
	{
		for (Vertex* ver : graphList.adjList[que.front()])
		{
			if (visited.find(ver) == visited.end())
			{
				que.push(ver);// 记录还需要访问的顶点
				visited.emplace(ver);// 记录访问过的顶点
				ret.emplace_back(ver);// 记录访问到的顶点
			}
		}
		que.pop();
	}
	return ret;
}
/*深度优先遍历*/
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
	vector<Vertex*> ret;// 顶点遍历序列
	unordered_set<Vertex*> visited;// 记录访问过的顶点
	// 递归遍历顶点
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
