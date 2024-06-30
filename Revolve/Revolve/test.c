#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//左旋或右旋，同理

void reverse(int* arr, int left, int right)
{
	while (left < right)
	{
		int tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
		left++;
		right--;
	}
}
//右旋
void revolve(int *arr,int sz,int k)
{
	//1 2 3 4 5 6 7       sz=7   k=3
	k %= sz;
	//旋转左侧
	reverse(arr, 0, sz - k - 1);
	//旋转右侧
	reverse(arr, sz - k, sz - 1);
	//整个旋转
	reverse(arr, 0, sz - 1);
}
int main()
{
	int arr[8] = { 0 };
	printf("输入8个数:>");
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		scanf("%d", &arr[i]);
	}
	int k = 0;
	printf("输入右旋的位数:>");
	scanf("%d", &k);
	revolve(arr, sizeof(arr) / sizeof(arr[0]), k);
	for (i = 0; i < 8; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}