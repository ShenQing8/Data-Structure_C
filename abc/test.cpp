#include <iostream>
#include <vector>
using namespace std;

char node[1100000000];

int cifang(int v, int n)
{
	int ret = 1;
	for(int i = 0; i < n; ++i)
	{
		ret *= v;
	}
	return ret;
}

void build_tree(int n, int k, char f)
{
	int left = cifang(2, n) + 2 * k - 2;
	node[left] = f;
	node[left + 1] = (f+1)%2;
}

int main()
{
	node[1] = 0;
	node[2] = 0;
	node[3] = 1;
	// 2,1   2
	// 3,1   4
	// 4,1   8
	// 5,1   16
	for(int i = 2; i < 15; ++i)
	{
		for(int j = 1; j <= cifang(2, i-1); ++j)
		{
			build_tree(i, j, node[cifang(2, i-1) + j - 1]);
		}
	}

	int n, k;
	cin >> n >> k;
	if(node[cifang(2, n-1) + k - 1] == 0)
		cout << "RED";
	else
		cout << "BLACK";

    return 0;
}


