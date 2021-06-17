#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>

/*
��������---��һ����Χ�ڵ���������ʱ�������καȽ������㷨��
ʱ�临�Ӷȣ�O(n+m)
�ռ临�Ӷȣ�O(n+m)
����˼·:
1.�ҳ��������������ֵ
2.����һ���������ֵΪ�������������ֵ������
3.��������������, �������������������ֵ������������
4.���������Ӧ�����洢ֵԭ�л�����+1
*/
void CountingSort(int *arry, int size) {
	assert(arry);
	//ͨ�����ֵ����Сֵ�������ʱ��������Ҫ���ٵĿռ��С
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
	// ������������
	int range = maxValue - minValue + 1;
	int *tArry = (int*)calloc(range, sizeof(int));
	memset(tArry, 0, range * sizeof(int));
	//ʹ����ʱ�����¼ԭʼ������ÿ�����ĸ���
	for (int i = 0; i < size; i++) {
		//ע�⣺�����ڴ洢��Ҫ��ԭʼ������ֵ�ϼ�ȥmin�Ų������Խ������
		tArry[arry[i] - minValue] += 1;
	}
	int index = 0;
	//����ͳ�ƽ�������¶�Ԫ�ؽ��л���
	for (int i = 0; i < range; i++) {
		while (tArry[i]--) {
			//ע�⣺Ҫ��i��ֵ����min���ܻ�ԭ��ԭʼ����
			arry[index++] = i + minValue;
		}
	}

	free(tArry);
}
// ��������Ԫ�ص�ֵ, i/j��Ҫ����������
void swapEle(int array[], int i, int j) {
	int temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}
/*
ѡ������
ʱ�临�Ӷȣ�O(n2)
�ռ临�Ӷȣ�O(1)
����˼·:
���谴����������
1.�õ�0��Ԫ�غͺ�������Ԫ�����αȽ�
2.�жϵ�0��Ԫ���Ƿ���ڵ�ǰ���Ƚ�Ԫ��, һ��С�ھͽ���λ��
3.��0��Ԫ�غͺ�������Ԫ�رȽ���ɺ�, ��0��Ԫ�ؾ�����Сֵ
4.�ų���0��Ԫ��, �õ�1��Ԫ���ظ�1~3����, �Ƚ���ɺ��1��Ԫ�ؾ��ǵ����ڶ�С��ֵ
�Դ�����, ֱ����ǰԪ��û�пɱȽϵ�Ԫ��, �������
*/
void SelectionSort(int *arry, int size) {
	// ���һλ���ñȽ�, Ҳû����һλ�����Ƚ�, �������ִ������    
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size - 1; j++) {
			// 1.�õ�ǰԪ�غͺ�������Ԫ�رȽ�            
			if (arry[i] > arry[j + 1]) {
				//  2.һ�����ִ��ھͽ���λ��                
				swapEle(arry, i, j + 1);
			}
		}
	}
}
/*
ð������
ʱ�临�Ӷȣ�O(n2)
�ռ临�Ӷȣ�O(1)
����˼·:
���谴����������
1.�ӵ�0��Ԫ�ؿ�ʼ, ÿ�ζ�����������Ԫ�ؽ��бȽ�
2.һ�����ֺ���һ��Ԫ��С��ǰ��һ��Ԫ�ؾͽ���λ��
3.����һ�ֱȽ�֮�����һ��Ԫ�ؾ������ֵ
4.�ų����һ��Ԫ��, �Դ�����, ÿ�αȽ����֮�����ֵ��������ٱ��Ƚ�����Ԫ�ص����
ֱ����ǰԪ��û�пɱȽϵ�Ԫ��, �������
*/
void BubbleSort(int *arry, int size) {
	for (int i = 0; i < size; i++) {
		// -1��ֹ`�Ǳ�Խ��`: ���ʵ��˲������Լ�������
		for (int j = 0; j < size - i - 1; j++) {
			//  1.�õ�ǰԪ�غ�����Ԫ�رȽ�
			if (arry[j] > arry[j + 1]) {
				//  2.һ�����ִ��ھͽ���λ��
				swapEle(arry, j, j + 1);
			}
		}
	}
}
/*
��������
ʱ�临�Ӷȣ�O(n2)
�ռ临�Ӷȣ�O(1)
����˼·:
���谴����������
1.������Ϊ1��Ԫ�ؿ�ʼ��ǰ�Ƚ�, һ��ǰ��һ��Ԫ�ش����Լ�����ǰ���Ԫ���Ⱥ��ƶ�
2.ֱ��û�пɱȽ�Ԫ�ػ���ǰ���Ԫ��С���Լ���ʱ��, �ͽ��Լ����뵽��ǰ�ճ�����λ��
*/
void InsertionSort(int *arry, int size) {
	//  1.�ӵ�һ��Ԫ�ؿ�ʼ����ȡ���������ڱȽ�Ԫ��
	for (int i = 1; i < size; i++)
	{
		// 2.ȡ�����ڱȽ�Ԫ��
		int temp = arry[i];
		int j = i;
		while (j > 0) {
			// 3.�ж�Ԫ���Ƿ�С��ǰһ��Ԫ��
			if (temp < arry[j - 1]) {
				// 4.��ǰһ��Ԫ������ƶ�һλ
				arry[j] = arry[j - 1];
			}
			else {
				break;
			}
			j--;
		}
		// 5.��Ԫ�ز��뵽�ճ�����λ��
		arry[j] = temp;
	}
}
/*
ϣ������
ʱ�临�Ӷȣ�O(n*log2n)
�ռ临�Ӷȣ�O(1)
����˼·:
1.ϣ������������Ϊ���������������, �Ƚ����������鰴��ָ����������Ϊ����С����
2.���ò��������С�����������, Ȼ�󽫼��������С�������ºϲ�Ϊԭʼ����
3.�ظ���������, ֱ������Ϊ1ʱ,�����ò����������򼴿�
*/
void ShellSort(int *arry, int size) {
	int h = 1;
	//���㲽��
	while (h < size / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		//����С������
		for (int i = h; i < size; i++) {
			//���ǰ��һ��Ԫ�ش��ڵ�ǰԪ��,�ͽ���λ��
			for (int j = i; j >= h && arry[j] < arry[j - h]; j -= h) {
				swapEle(arry, j, j - h);
			}
		}
		//���¼��㲽��
		h = h / 3;
	}
}
//���������㷨
int quicksort_r(int* a, int start, int end) {
	if (start >= end) {
		return 0;
	}
	int pivot = a[end];
	int swp;
	int pointer = start;
	for (int i = start; i < end; i++) {
		//���ȵ�һ��С���Ƶ�ǰ��
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
	//ǰ��ݹ�
	quicksort_r(a, start, pointer - 1);
	//���ݹ�
	quicksort_r(a, pointer + 1, end);
	return 0;
}
/*
��������
ʱ�临�Ӷȣ�O(n*log2n)
�ռ临�Ӷȣ�O(log2n)
����˼·:
1.ѡȡһ����Ϊ��׼
2.���Ȼ�׼С����������ǰ�棬�Ȼ�׼���������������
3.�����������ظ��ڶ�����ֱ��������ֻ��һ����
*/
void QuickSort(int *arry, int size) {
	quicksort_r(arry, 0, size - 1);
}
// �����򣺣����ѣ������������ӶѶ��Ѹ�ж��������������֮ǰ���ٻָ��ѡ�
void max_heapify(int arr[], int start, int end) {
	//�������ڵ�ָ����ӽڵ�ָ��
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { //���ӽڵ��ڷ�Χ�ڲ����Ƚ�
		if (son + 1 <= end && arr[son] < arr[son + 1]) //�ȱȽ������ӽڵ�ָ�꣬ѡ������
			son++;
		if (arr[dad] > arr[son]) //������ڵ�����ӽڵ���������ɣ�ֱ����������
			return;
		else { //���򽻻����Ӄ����ټ����ӽڵ�����ڵ���^
			swapEle(arr, dad, son);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}
/*
������
ʱ�临�Ӷȣ�O(n*log2n)
�ռ临�Ӷȣ�O(1)
����˼·:
1.����ʼ������ؼ�������(R1,R2��.Rn)�����ɴ󶥶ѣ��˶�Ϊ��ʼ��������
2.���Ѷ�Ԫ��R[1]�����һ��Ԫ��R[n]��������ʱ�õ��µ�������(R1,R2,����Rn-1)���µ�������(Rn),������R[1,2��n-1]<=R[n]
3.���ڽ������µĶѶ�R[1]����Υ���ѵ����ʣ������Ҫ�Ե�ǰ������(R1,R2,����Rn-1)����Ϊ�¶ѣ�Ȼ���ٴν�R[1]�����������һ��Ԫ�ؽ������õ��µ�������(R1,R2��.Rn-2)���µ�������(Rn-1,Rn)
4.�����ظ��˹���ֱ����������Ԫ�ظ���Ϊn-1������������������
*/
void HeapSort(int *arry, int size) {
	//��ʼ����i�����һ�����ڵ㿪ʼ����
	for (int i = size / 2 - 1; i >= 0; i--)
		max_heapify(arry, i, size - 1);
	//�Ƚ���һ��Ԫ�غ��Ѿ��źõ�Ԫ��ǰһλ���������ٴ��µ���(�յ�����Ԫ��֮ǰ��Ԫ��)��ֱ���������
	for (int i = size - 1; i > 0; i--) {
		swapEle(arry, 0, i);
		max_heapify(arry, 0, i - 1);
	}
}
//�鲢�㷨
void Merge(int *arry, int start, int mid, int end)
{
	int *temp = (int *)malloc((end - start + 1) * sizeof(int));    //����ռ�����������������鲢�����ʱ����
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
//�����ж԰���ֱ�����г���Ϊ1
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
�鲢����
ʱ�临�Ӷȣ�O(n*log2n)
�ռ临�Ӷȣ�O(n)
����˼·��
1.�ѳ���Ϊn���������зֳ���������Ϊn/2��������
2. �������������зֱ���ù鲢����
3. ����������õ������кϲ���һ�����յ���������
*/
void MergeSort(int *arry, int size) {
	int start = 0;
	int end = size - 1;
	MergeSort_r(arry, start, end);
}
//���δ��������������һ��Ԫ��ֵ
int GetMaxVal(int* arr, int len)
{
	int maxVal = arr[0]; //�������Ϊarr[0]
	for (int i = 1; i < len; i++)  //�����Ƚϣ��ҵ���ľ͸�ֵ��maxVal
	{
		if (arr[i] > maxVal) {
			maxVal = arr[i];
		}
	}
	return maxVal;  //�������ֵ
}
/*
Ͱ����
ʱ�临�Ӷȣ�O(n)
�ռ临�Ӷȣ�O(m)
����˼·��
1.����һ�����������鵱����Ͱ��
2.Ѱ�����У����Ұ���Ŀһ��һ���ŵ���Ӧ��Ͱ��ȥ
3.��ÿ�����ǿյ�Ͱ�ӽ�������
4.�Ӳ��ǿյ�Ͱ�������Ŀ�ٷŻ�ԭ����������
*/
void BucketSort(int *arry, int size) {
	int tmpArrLen = GetMaxVal(arry, size) + 1;
	int *tmpArr = (int *)calloc(tmpArrLen, sizeof(int));  //��ÿ�Ͱ��С
	int i, j;

	for (i = 0; i < tmpArrLen; i++)  //��Ͱ��ʼ��
		tmpArr[i] = 0;

	for (i = 0; i < size; i++)   //Ѱ�����У����Ұ���Ŀһ��һ���ŵ���Ӧ��Ͱ��ȥ��
		tmpArr[arry[i]]++;

	for (i = 0, j = 0; i < tmpArrLen; i++)
	{
		while (tmpArr[i] != 0) //��ÿ�����ǿյ�Ͱ�ӽ�������
		{
			arry[j] = i;  //�Ӳ��ǿյ�Ͱ�������Ŀ�ٷŻ�ԭ���������С�
			j++;
			tmpArr[i]--;
		}
	}
	free(tmpArr);
}
//���������������ݵ����λ��
int maxbit(int data[], int n) {
	int maxData = data[0];		///< �����
	/// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
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
��������
ʱ�临�Ӷȣ�O(k*n)
�ռ临�Ӷȣ�
����˼·��
1.ȡ�������е����������ȡ��λ��
2.arrΪԭʼ���飬�����λ��ʼȡÿ��λ���radix����
3.��radix���м����������ü�������������С��Χ�����ص㣩
*/
void radixsort(int *arry, int size) {
	int d = maxbit(arry, size);
	int *tmp = new int[size];
	int *count = new int[10]; //������
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //ÿ�η���ǰ��ռ�����
		for (j = 0; j < size; j++)
		{
			k = (arry[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
		for (j = size - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (arry[j] / radix) % 10;
			tmp[count[k] - 1] = arry[j];
			count[k]--;
		}
		for (j = 0; j < size; j++) //����ʱ��������ݸ��Ƶ�data��
			arry[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}