#include <iostream>
#include <vector>
using namespace std;

/*基于邻接矩阵实现图*/
class GraphAdjMat
{
public:
	vector<int> vertices;       // 顶点列表，元素代表“顶点值”，索引代表“顶点索引”
	vector<vector<bool>> adjMat; // 邻接矩阵，行列索引对应“顶点索引”

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
