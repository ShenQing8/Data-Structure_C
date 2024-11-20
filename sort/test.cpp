#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
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

/*堆排序*/
void siftDown(vector<int>& nums, int n, int i)// 从堆顶至底堆化
{
    while(1)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if(l < n && nums[l] > nums[ma])
            ma = l;
        if(r < n && nums[r] > nums[ma])
            ma = r;
        
        if(i == ma)
            break;
        
        swap(nums[i], nums[ma]);
        i = ma;
    }
}
void heapSort(vector<int>& nums)// 大顶堆
{
    int n = nums.size();// 未排序数组的长度
    for(int i = n / 2 - 1; i >= 0; --i)// 将原数组堆化为大顶堆
    {
        siftDown(nums, n, i);
    }
    while(n > 1)
    {
        swap(nums[0], nums[n - 1]);
        --n;
        siftDown(nums, n, 0);
    }
}
// 上述几种排序算法都属于“基于比较的排序算法”，它们通过比较元素间的大小来实现排序。此类排序算法的时间复杂度无法超越 O(nlog(n))
// 下面，我们将探讨几种“非比较排序算法”，它们的时间复杂度可以达到线性阶。

/*桶排序*/
// 桶排序适用于处理体量很大的数据。
// 例如，输入数据包含 100 万个元素，由于空间限制，系统内存无法一次性加载所有数据。
// 此时，可以将数据分成 1000 个桶，然后分别对每个桶进行排序，最后将结果合并。
void bucketSort(vector<float> &nums)
{// 假设所有数据的输入范围为[0,1)
    int k = nums.size() / 2;// 定义 k 个桶，理想情况为每个桶有两个数据
    vector<vector<float>> buckets(k);
    // 1、将元素分配到各个桶中
    for(float val: nums)
    {
        // 输入范围为[0,1)，则val * k可映射到[0,k-1]的桶中
        int i = val * k;
        buckets[i].emplace_back(val);
    }
    // 2、排序每个桶中的元素
    for(vector<float>& bucket: buckets)
    {
        sort(bucket.begin(), bucket.end());
    }
    // 3、合并每个桶
    int i = 0;
    for(vector<float>& bucket: buckets)
    {
        for (float val: bucket)
        {
            nums[i++] = val;
        }
    }
}

/*计数排序*/
// 1、只适用于非负整数。若想将其用于其他类型的数据，需要确保这些数据可以转换为非负整数，并且在转换过程中不能改变各个元素之间的相对大小关系
// 2、适用于数据量大但数据范围小的情况
void countingSort(vector<int>& nums)
{
    // 找出最大的数m
    int m = 0;
    for(int num: nums)
        m = num > m ? num : m;
    // 创建容量为m+1的数组，并统计前缀
    vector<int> counter(m+1, 0);
    for(int num: nums)
        ++counter[num];
    // 统计前缀和
    for(int i = 1; i < m+1; ++i)
        counter[i] += counter[i-1];
    // 倒叙遍历数组，将元素填入res中
    int n = nums.size();
    vector<int> res(n);
    for(int i = n-1; i >=0; --i)
    {
        res[counter[nums[i]] - 1] = nums[i];
        --counter[nums[i]];
    }
    // 排序后的数组覆盖原数组
    nums = res;
}

/*基数排序*/ // 以十进制数为例
// 得到当前位的数：(num/(d^k-1))%d
// d位进制数，k为位数
int digit(int num, int exp) // exp = 10^(k-1)
{
    return (num / exp) % 10;
}
void countingSortDigit(vector<int>& nums, int exp)
{
    // 由于是十进制数，所以最大数是9
    vector<int> counter(10, 0);
    for (int num : nums)
    {
        int n = digit(num, exp);
        ++counter[n];
    }
    // 计算前缀和
    for (int i = 1; i < 10; ++i)
        counter[i] += counter[i - 1];
    // 倒序遍历师数组
    int n = nums.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i)
    {
        int n = digit(nums[i], exp);
        res[counter[n] - 1] = nums[i];
        --counter[n];
    }
    // 排序后的数组覆盖原数组
    nums = res;
}
void radixSort(vector<int>& nums)
{
    // 获取数组中的最大元素
    int m = *max_element(nums.begin(), nums.end());
    // 从个位一直排序到最高位
    for (int exp = 1; exp <= m; exp *= 10)
    {
        // 按第 i 位数排序
        countingSortDigit(nums, exp);
    }
}



int main()
{
//    vector<int> nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
//    /*插入排序*/
//    insertionSort(nums);
//
//    /*快排*/
//    nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
//    quicksort(nums, 0, nums.size()-1);
//
//    /*归并排序*/
//    nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
//    mergeSort(nums, 0, nums.size()-1);
//
//    /*堆排序*/
//    nums = {16,4,3,5,6,7,9,4,56,54,82,95,46,78};
//    heapSort(nums);
//
//    /*桶排序*/
//    vector<float> buc_nums = {0.1, 0.02, 0.34, 0.78, 0.16, 0.99, 0.45, 0.46, 0.55};
//    bucketSort(buc_nums);
//
//    /*计数排序*/
//    vector<int> coun_nums = {2,3,5,1,6,8,9,4,8,5,6,15,13};
//    countingSort(coun_nums);

    /*基数排序*/
    vector<int> rad_nums = {202312345, 202313526, 202366789, 2134, 56789, 999999};
    radixSort(rad_nums);

    return 0;
}
