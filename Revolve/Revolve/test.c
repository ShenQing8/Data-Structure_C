#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//������������ͬ��

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
//����
void revolve(int *arr,int sz,int k)
{
	//1 2 3 4 5 6 7       sz=7   k=3
	k %= sz;
	//��ת���
	reverse(arr, 0, sz - k - 1);
	//��ת�Ҳ�
	reverse(arr, sz - k, sz - 1);
	//������ת
	reverse(arr, 0, sz - 1);
}
int main()
{
	int arr[8] = { 0 };
	printf("����8����:>");
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		scanf("%d", &arr[i]);
	}
	int k = 0;
	printf("����������λ��:>");
	scanf("%d", &k);
	revolve(arr, sizeof(arr) / sizeof(arr[0]), k);
	for (i = 0; i < 8; i++)
	{
		printf("%d ", arr[i]);
	}
	return 0;
}