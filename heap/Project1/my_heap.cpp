#include <iostream>
#include <vector>
using namespace std;
// ����һ��������������ȫ����������Ϊ�󶥶Ѻ�С����
// ��������ʵ�֣������algorithmͷ�ļ�
// ���Ƕ�ͨ������ʵ�����ȶ��У�c++��queueͷ�ļ�������priority_queue��ʵ��
// �ѱ�������vectorʵ�ֵģ�priority_queueһ�����Ҳ��vectorʵ�֣�Ҳ���ñ�ģ����CSDN�ղأ�
// ��ʹ�÷��濴�����߲�������

// ��ȫ�������ǳ��ʺ�����������ʾ�����ڶ�����һ����ȫ��������������ǽ������������洢�ѡ�


class Heap
{
public:
	vector<int> myHeap;

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

	/*���ʶѶ�Ԫ��*/
	int peek()
	{
		return myHeap[0];
	}

	/*���¶��ϵ���*/
	void siftUp()
	{
		int i = myHeap.size() - 1;
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
	void siftDown()
	{
		int i = 0;
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

	/*Ԫ�����*/
	void push(int val)
	{
		// ���
		myHeap.push_back(val);
		// ������
		siftUp();
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
	}
};


int main()
{
	
	return 0;
}
