#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>

/*
计数排序---对一定范围内的整数排序时，快于任何比较排序算法。
时间复杂度：O(n+m)
空间复杂度：O(n+m)
排序思路:
1.找出待排序数组最大值
2.定义一个索引最大值为待排序数组最大值的数组
3.遍历待排序数组, 将待排序数组遍历到的值作新数组索引
4.在新数组对应索引存储值原有基础上+1
*/
void CountingSort(int *arry, int size) {
	assert(arry);
	//通过最大值和最小值计算出临时数组所需要开辟的空间大小
	int maxValue = arry[0];
	int minValue = arry[0];
	for (int i = 0; i < size; i++) {
		if (arry[i] > maxValue) {
			maxValue = arry[i];
		}
		if (arry[i] < minValue) {
			minValue = arry[i];
		}
	}
	// 用于排序数组
	int range = maxValue - minValue + 1;
	int *tArry = (int*)calloc(range, sizeof(int));
	memset(tArry, 0, range * sizeof(int));
	//使用临时数组记录原始数组中每个数的个数
	for (int i = 0; i < size; i++) {
		//注意：这里在存储上要在原始数组数值上减去min才不会出现越界问题
		tArry[arry[i] - minValue] += 1;
	}
	int index = 0;
	//根据统计结果，重新对元素进行回收
	for (int i = 0; i < range; i++) {
		while (tArry[i]--) {
			//注意：要将i的值加上min才能还原到原始数据
			arry[index++] = i + minValue;
		}
	}

	free(tArry);
}
// 交换两个元素的值, i/j需要交换的索引
void swapEle(int array[], int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}
/*
选择排序
时间复杂度：O(n2)
空间复杂度：O(1)
排序思路:
假设按照升序排序
1.用第0个元素和后面所有元素依次比较
2.判断第0个元素是否大于当前被比较元素, 一旦小于就交换位置
3.第0个元素和后续所有元素比较完成后, 第0个元素就是最小值
4.排除第0个元素, 用第1个元素重复1~3操作, 比较完成后第1个元素就是倒数第二小的值
以此类推, 直到当前元素没有可比较的元素, 排序完成
*/
void SelectionSort(int *arry, int size) {
	// 最后一位不用比较, 也没有下一位和它比较, 否则会出现错误访问    
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size - 1; j++) {
			// 1.用当前元素和后续所有元素比较            
			if (arry[i] > arry[j + 1]) {
				//  2.一旦发现大于就交换位置                
				swapEle(arry, i, j + 1);
			}
		}
	}
}
/*
冒泡排序
时间复杂度：O(n2)
空间复杂度：O(1)
排序思路:
假设按照升序排序
1.从第0个元素开始, 每次都用相邻两个元素进行比较
2.一旦发现后面一个元素小于前面一个元素就交换位置
3.经过一轮比较之后最后一个元素就是最大值
4.排除最后一个元素, 以此类推, 每次比较完成之后最大值都会出现再被比较所有元素的最后
直到当前元素没有可比较的元素, 排序完成
*/
void BubbleSort(int *arry, int size) {
	for (int i = 0; i < size; i++) {
		// -1防止`角标越界`: 访问到了不属于自己的索引
		for (int j = 0; j < size - i - 1; j++) {
			//  1.用当前元素和相邻元素比较
			if (arry[j] > arry[j + 1]) {
				//  2.一旦发现大于就交换位置
				swapEle(arry, j, j + 1);
			}
		}
	}
}
/*
插入排序
时间复杂度：O(n2)
空间复杂度：O(1)
排序思路:
假设按照升序排序
1.从索引为1的元素开始向前比较, 一旦前面一个元素大于自己就让前面的元素先后移动
2.直到没有可比较元素或者前面的元素小于自己的时候, 就将自己插入到当前空出来的位置
*/
void InsertionSort(int *arry, int size) {
	//  1.从第一个元素开始依次取出所有用于比较元素
	for (int i = 1; i < size; i++)
	{
		// 2.取出用于比较元素
		int temp = arry[i];
		int j = i;
		while (j > 0) {
			// 3.判断元素是否小于前一个元素
			if (temp < arry[j - 1]) {
				// 4.让前一个元素向后移动一位
				arry[j] = arry[j - 1];
			}
			else {
				break;
			}
			j--;
		}
		// 5.将元素插入到空出来的位置
		arry[j] = temp;
	}
}
/*
希尔排序
时间复杂度：O(n*log2n)
空间复杂度：O(1)
排序思路:
1.希尔排序可以理解为插入排序的升级版, 先将待排序数组按照指定步长划分为几个小数组
2.利用插入排序对小数组进行排序, 然后将几个排序的小数组重新合并为原始数组
3.重复上述操作, 直到步长为1时,再利用插入排序排序即可
*/
void ShellSort(int *arry, int size) {
	int h = 1;
	//计算步长
	while (h < size / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		//进行小组排序
		for (int i = h; i < size; i++) {
			//如果前面一个元素大于当前元素,就交换位置
			for (int j = i; j >= h && arry[j] < arry[j - h]; j -= h) {
				swapEle(arry, j, j - h);
			}
		}
		//重新计算步长
		h = h / 3;
	}
}
//快速排序算法
int quicksort_r(int* a, int start, int end) {
	if (start >= end) {
		return 0;
	}
	int pivot = a[end];
	int swp;
	int pointer = start;
	for (int i = start; i < end; i++) {
		//将比第一个小的移到前面
		if (a[i] < pivot) {
			if (pointer != i) {
				swp = a[i];
				a[i] = a[pointer];
				a[pointer] = swp;
			}
			pointer++;
		}
	}
	swp = a[end];
	a[end] = a[pointer];
	a[pointer] = swp;
	//前半递归
	quicksort_r(a, start, pointer - 1);
	//后半递归
	quicksort_r(a, pointer + 1, end);
	return 0;
}
/*
快速排序
时间复杂度：O(n*log2n)
空间复杂度：O(log2n)
排序思路:
1.选取一个数为基准
2.将比基准小的数交换到前面，比基准大的数交换到后面
3.对左右区间重复第二步，直到各区间只有一个数
*/
void QuickSort(int *arry, int size) {
	quicksort_r(arry, 0, size - 1);
}
// 堆排序：（最大堆，有序区）。从堆顶把根卸出来放在有序区之前，再恢复堆。
void max_heapify(int arr[], int start, int end) {
	//建立父节点指标和子节点指标
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { //若子节点在范围内才做比较
		if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点指标，选择最大的
			son++;
		if (arr[dad] > arr[son]) //如果父节点大于子节点代表调整完成，直接跳出函数
			return;
		else { //否则交换父子內容再继续子节点与孙节点比較
			swapEle(arr, dad, son);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}
/*
堆排序
时间复杂度：O(n*log2n)
空间复杂度：O(1)
排序思路:
1.将初始待排序关键字序列(R1,R2….Rn)构建成大顶堆，此堆为初始的无序区
2.将堆顶元素R[1]与最后一个元素R[n]交换，此时得到新的无序区(R1,R2,……Rn-1)和新的有序区(Rn),且满足R[1,2…n-1]<=R[n]
3.由于交换后新的堆顶R[1]可能违反堆的性质，因此需要对当前无序区(R1,R2,……Rn-1)调整为新堆，然后再次将R[1]与无序区最后一个元素交换，得到新的无序区(R1,R2….Rn-2)和新的有序区(Rn-1,Rn)
4.不断重复此过程直到有序区的元素个数为n-1，则整个排序过程完成
*/
void HeapSort(int *arry, int size) {
	//初始化，i从最后一个父节点开始调整
	for (int i = size / 2 - 1; i >= 0; i--)
		max_heapify(arry, i, size - 1);
	//先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完成
	for (int i = size - 1; i > 0; i--) {
		swapEle(arry, 0, i);
		max_heapify(arry, 0, i - 1);
	}
}
//归并算法
void Merge(int *arry, int start, int mid, int end)
{
	int *temp = (int *)malloc((end - start + 1) * sizeof(int));    //申请空间来存放两个有序区归并后的临时区域
	int i = start;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= end) {
		if (arry[i] <= arry[j]) {
			temp[k++] = arry[i++];
		}
		else {
			temp[k++] = arry[j++];
		}
	}
	while (i <= mid) {
		temp[k++] = arry[i++];
	}
	while (j <= end) {
		temp[k++] = arry[j++];
	}
	for (i = 0; i < k; i++) {
		arry[start + i] = temp[i];
	}
	free(temp);
}
//将序列对半拆分直到序列长度为1
void MergeSort_r(int *arry, int start, int end) {
	int mid = start + (end - start) / 2;
	if (start >= end) {
		return;
	}
	MergeSort_r(arry, start, mid);
	MergeSort_r(arry, mid + 1, end);

	Merge(arry, start, mid, end);
}
/*
归并排序
时间复杂度：O(n*log2n)
空间复杂度：O(n)
排序思路：
1.把长度为n的输入序列分成两个长度为n/2的子序列
2. 对这两个子序列分别采用归并排序
3. 将两个排序好的子序列合并成一个最终的排序序列
*/
void MergeSort(int *arry, int size) {
	int start = 0;
	int end = size - 1;
	MergeSort_r(arry, start, end);
}
//获得未排序数组中最大的一个元素值
int GetMaxVal(int* arr, int len)
{
	int maxVal = arr[0]; //假设最大为arr[0]
	for (int i = 1; i < len; i++)  //遍历比较，找到大的就赋值给maxVal
	{
		if (arr[i] > maxVal) {
			maxVal = arr[i];
		}
	}
	return maxVal;  //返回最大值
}
/*
桶排序
时间复杂度：O(n)
空间复杂度：O(m)
排序思路：
1.设置一个定量的数组当作空桶子
2.寻访序列，并且把项目一个一个放到对应的桶子去
3.对每个不是空的桶子进行排序
4.从不是空的桶子里把项目再放回原来的序列中
*/
void BucketSort(int *arry, int size) {
	int tmpArrLen = GetMaxVal(arry, size) + 1;
	int *tmpArr = (int *)calloc(tmpArrLen, sizeof(int));  //获得空桶大小
	int i, j;

	for (i = 0; i < tmpArrLen; i++)  //空桶初始化
		tmpArr[i] = 0;

	for (i = 0; i < size; i++)   //寻访序列，并且把项目一个一个放到对应的桶子去。
		tmpArr[arry[i]]++;

	for (i = 0, j = 0; i < tmpArrLen; i++)
	{
		while (tmpArr[i] != 0) //对每个不是空的桶子进行排序。
		{
			arry[j] = i;  //从不是空的桶子里把项目再放回原来的序列中。
			j++;
			tmpArr[i]--;
		}
	}
	free(tmpArr);
}
//辅助函数，求数据的最大位数
int maxbit(int data[], int n) {
	int maxData = data[0];		///< 最大数
	/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < n; ++i)
	{
		if (maxData < data[i])
			maxData = data[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		//p *= 10; // Maybe overflow
		maxData /= 10;
		++d;
	}
	return d;
}
/*
基数排序
时间复杂度：O(k*n)
空间复杂度：
排序思路：
1.取得数组中的最大数，并取得位数
2.arr为原始数组，从最低位开始取每个位组成radix数组
3.对radix进行计数排序（利用计数排序适用于小范围数的特点）
*/
void radixsort(int *arry, int size) {
	int d = maxbit(arry, size);
	int *tmp = new int[size];
	int *count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < size; j++)
		{
			k = (arry[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = size - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (arry[j] / radix) % 10;
			tmp[count[k] - 1] = arry[j];
			count[k]--;
		}
		for (j = 0; j < size; j++) //将临时数组的内容复制到data中
			arry[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}