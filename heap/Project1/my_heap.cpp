#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// 堆是一种满足条件的完全二叉树，分为大顶堆和小顶堆
// 堆自身有实现，需包含algorithm头文件
// 但是堆通常用于实现优先队列，c++的queue头文件包含了priority_queue的实现
// 堆本身是用vector实现的，priority_queue一般而言也用vector实现（也可用别的，详见CSDN收藏）
// 从使用方面看，二者并无区别

// 完全二叉树非常适合用数组来表示。由于堆正是一种完全二叉树，因此我们将采用数组来存储堆。


class MaxHeap
{
private:
	/*获取左子节点*/
	int left(int i)// 接收下标
	{
		return 2 * i + 1;
	}
	/*获取右子节点*/
	int right(int i)
	{
		return 2 * i + 2;
	}
	/*获取父节点*/
	int parent(int i)
	{
		return (i - 1) / 2;// 向下取整
	}
	/*自下而上调整*/
	void siftUp(int i)
	{
		int p = parent(i);
		while (p >= 0)
		{
			if (myHeap[i] > myHeap[p])
				swap(myHeap[i], myHeap[p]);
			else
				break;
			i = p;
			p = parent(i);
		}
	}
	/*自上而下调整*/
	void siftDown(int i)
	{
		int l = left(i);
		int r = right(i);
		int sz = myHeap.size();
		while (l < sz && r < sz)
		{
			int m = myHeap[l] > myHeap[r] ? l : r;
			if (myHeap[i] < myHeap[m])
				swap(myHeap[i], myHeap[m]);
			else
				break;
			i = m;
			l = left(i);
			r = right(i);
		}
	}
public:
	vector<int> myHeap;
	
	/*建堆*/
	MaxHeap(vector<int>& input)
	{
		myHeap = input;
		// 堆化除叶节点以外的其他节点
		for (int i = parent(myHeap.size() - 1); i >= 0; --i)
			siftDown(i);
	}

	/*访问堆顶元素*/
	int peek()
	{
		return myHeap[0];
	}

	/*元素入堆*/
	void push(int val)
	{
		// 入堆
		myHeap.push_back(val);
		// 调整堆
		siftUp(myHeap.size() - 1);
	}
	/*元素出堆*/
	void pop()
	{
		if (myHeap.empty())
			cout << "堆为空" << endl;
		// 先交换
		swap(myHeap[0], myHeap[myHeap.size() - 1]);
		// 再删除最后一个元素
		myHeap.pop_back();
		// 自上而下调整
		siftDown(0);
	}
};

/*关于堆的 Top-K 问题*/
priority_queue<int, vector<int>, greater<int>> topkHeap(vector<int>& nums,int k)
{
	priority_queue<int, vector<int>, greater<int>> ret;
	// 初始化一个大小为 k 的小顶堆
	for (int i = 0; i < k; ++i)
		ret.push(nums[i]);
	// 循环剩余 n-k 个元素，如果有大于堆顶元素的，替换掉
	for (int i = nums.size() - 1; i >= k; --i)
		if (nums[i] > ret.top())
		{
			ret.pop();
			ret.push(nums[i]);
		}
	return ret;
}
void topK()
{
	// 给定一个长度为 n 的无序数组 nums ，请返回数组中最大的 k 个元素。
	vector<int> nums = { 2,6,4,1,8,9,23,41,20,37,56 };
	priority_queue<int, vector<int>, greater<int>> topk = topkHeap(nums, 3);
}

int main()
{
	vector<int> nums = { 2,6,4,1,8,9,23,41,20,37,56 };
	MaxHeap maxHeap(nums);
	topK();
	return 0;
}
