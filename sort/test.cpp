#include <iostream>
#include <vector>
using namespace std;

/*插入排序*/
void insertionSort(vector<int>& nums)
{
    for(int i = 1; i < nums.size(); ++i)
    {
        int base = nums[i];
        int j = i;
        while(j > 0 && base < nums[j-1])
        {
            nums[j] = nums[j-1];
            --j;
        }
        nums[j] = base;
    }
}

/*快排*/
void medianThree(vector<int>& nums, int left, int right)
{
    int mid = left + (right - left)/2;
    if((nums[mid] < nums[left] && nums[mid] > nums[right]) || (nums[mid] < nums[right] && nums[mid] > nums[left]))
        swap(nums[mid], nums[left]);// nums[mid]在nums[left]和nums[right]中间
    else if((nums[right] < nums[left] && nums[right] > nums[mid]) || (nums[right] < nums[mid] && nums[right] > nums[left]))
        swap(nums[right], nums[left]);// nums[right]在中间
    return;
}
void quicksort(vector<int>& nums, int left, int right)
{
    if(left >= right)// 当数组长度小于等于 1 时，不用排序
        return;
    medianThree(nums, left, right);// 基准数优化，减小排序算法时间复杂度劣化至O(n^2)的概率
    int i = left;
    int j = right;
    while(i < j)
    {
        while(i < j && nums[j] >= nums[left])
            --j;
        while(i < j && nums[i] <= nums[left])
            ++i;
        swap(nums[i], nums[j]);
    }
    swap(nums[left], nums[i]);

    quicksort(nums, left, i - 1);// 继续排序左边
    quicksort(nums, i + 1, right);// 继续排序右边
}

/*归并排序*/
void merge(vector<int>& nums, int left, int mid, int right)
{
    // 创建临时数组用来存储排序后的数据
    vector<int> tmp(right - left + 1);
    // 比较左右两子数组中的数
    int i = left, j = mid + 1, k = 0;
    while(i <= mid && j <= right)
    {
        if(nums[i] <= nums[j])// 用 <= 而不是 < 是为了保证排序的稳定性
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    // 把左子树中剩余的数填充进临时数组
    while(i <= mid)
        tmp[k++] = nums[i++];
    // 把右子树中剩余的数填充进临时数组
    while(j <= right)
        tmp[k++] = nums[j++];
    // 把临时数组中的数据拷贝到原数组中
    for(i = 0; i < right - left + 1; ++i)
    {
        nums[left + i] = tmp[i];
    }
}
void mergeSort(vector<int>& nums, int left, int right)
{
    if(left >= right)// 当子数组元素数量小于等于1时，直接返回
        return;
    int mid = left + (right - left)/2;
    // 递归左子数组
    mergeSort(nums, left, mid);
    // 递归右子数组
    mergeSort(nums, mid+1, right);
    // 合并两个子数组
    merge(nums, left, mid, right);
}

int main()
{
    vector<int> nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
    /*插入排序*/
    insertionSort(nums);

    /*快排*/
    nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
    quicksort(nums, 0, nums.size()-1);

    /*归并排序*/
    nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
    mergeSort(nums, 0, nums.size()-1);

    return 0;
}
