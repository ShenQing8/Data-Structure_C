#include <iostream>
#include <queue>
#include <vector>
using namespace std;
// ����һ��������������ȫ����������Ϊ�󶥶Ѻ�С����
// ��������ʵ�֣������algorithmͷ�ļ�
// ���Ƕ�ͨ������ʵ�����ȶ��У�c++��queueͷ�ļ�������priority_queue��ʵ��
// �ѱ�������vectorʵ�ֵģ�priority_queueһ�����Ҳ��vectorʵ�֣�Ҳ���ñ�ģ����CSDN�ղأ�
// ��ʹ�÷��濴�����߲�������

// ��ȫ�������ǳ��ʺ�����������ʾ�����ڶ�����һ����ȫ��������������ǽ������������洢�ѡ�


class MaxHeap
{
private:
	/*��ȡ���ӽڵ�*/
	int left(int i)// �����±�
	{
		return 2 * i + 1;
	}
	/*��ȡ���ӽڵ�*/
	int right(int i)
	{
		return 2 * i + 2;
	}
	/*��ȡ���ڵ�*/
	int parent(int i)
	{
		return (i - 1) / 2;// ����ȡ��
	}
	/*���¶��ϵ���*/
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
	/*���϶��µ���*/
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
	
	/*����*/
	MaxHeap(vector<int>& input)
	{
		myHeap = input;
		// �ѻ���Ҷ�ڵ�����������ڵ�
		for (int i = parent(myHeap.size() - 1); i >= 0; --i)
			siftDown(i);
	}

	/*���ʶѶ�Ԫ��*/
	int peek()
	{
		return myHeap[0];
	}

	/*Ԫ�����*/
	void push(int val)
	{
		// ���
		myHeap.push_back(val);
		// ������
		siftUp(myHeap.size() - 1);
	}
	/*Ԫ�س���*/
	void pop()
	{
		if (myHeap.empty())
			cout << "��Ϊ��" << endl;
		// �Ƚ���
		swap(myHeap[0], myHeap[myHeap.size() - 1]);
		// ��ɾ�����һ��Ԫ��
		myHeap.pop_back();
		// ���϶��µ���
		siftDown(0);
	}
};

/*���ڶѵ� Top-K ����*/
priority_queue<int, vector<int>, greater<int>> topkHeap(vector<int>& nums,int k)
{
	priority_queue<int, vector<int>, greater<int>> ret;
	// ��ʼ��һ����СΪ k ��С����
	for (int i = 0; i < k; ++i)
		ret.push(nums[i]);
	// ѭ��ʣ�� n-k ��Ԫ�أ�����д��ڶѶ�Ԫ�صģ��滻��
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
	// ����һ������Ϊ n ���������� nums ���뷵������������ k ��Ԫ�ء�
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
