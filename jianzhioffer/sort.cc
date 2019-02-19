/*
一、排序算法
	1.蒂姆排序---暂时不看
	2.冒泡
	3.直接选择排序
	4.直接插入排序
	5.快速排序
	6.归并排序
	7.堆排序

二、数据结构
	1.完全二叉树定义
	2.二叉树的先序、中序、后序遍历(循环、递归实现），层序遍历，深度优先、广度优先遍历
	3.二叉树的高度
	4.平衡二叉树构建、插入、删除
	5.红黑树
	6.b+ b-树---暂时不看

三、其他算法
	1.贪心算法
	2.动态规划

四、多线程相关

五、网络模型
	1.TPC/IP协议模型 三次握手

六、编程语言相关
	1.模板
	2.type_traits

七、Windows平台相关
	1.Windows消息运行机制

*/


#include <vector>
using namespace std;

void print_arr(vector<int> &v) {
	printf("res:");
	for (auto val : v) {
		printf("%d,", val);
	}
	printf("\n");
}


/************************************************************************************************排序方法******************************************************************************************/


/************************************************************************/
/* 快速排序                 
0.选择一个枢纽元素，为其找到在序列中的正确位置，使其左边元素比其小，右边元素比其大。
1.重复上述步骤。
*/
/************************************************************************/

int Partition(vector<int>& v, int start, int end) {
	
	int key_pos = start;
	int i = key_pos, j = end;

	while (i < j) {
		while (i < j && v[i] < v[key_pos]) ++i;
		while (i < j && v[j] > v[key_pos] ) --j;
		swap(v[i], v[j]);
	}

	swap(v[i], v[key_pos]);

	return i;
}

void DoQuickSort(vector<int>& v, int start, int end) {
	if (start < end) {
		int index = Partition(v, start, end);
		DoQuickSort(v, start, index-1);
		DoQuickSort(v, index + 1, end);
	}
}

void QuickSort(vector<int>& v) {
	DoQuickSort(v, 0, v.size() - 1);
}



/************************************************************************/
/*归并排序
0.将无序序列分解为子序列
1.将子序列排序
2.将排序好的子序列两两进行归并
*/
/************************************************************************/
void Merge(vector<int>& v, int start, int mid, int end) {
	int i = start, m = mid;
	int j = mid + 1, n = end;

	vector<int> tmp;
	while (i <= m && j <= n) {
		if (v[i] > v[j]) tmp.push_back( v[j++]);
		else tmp.push_back( v[i++]);
	}
	while (i <= m) tmp.push_back(v[i++]);
	while (j <= n) tmp.push_back(v[j++]);

	int t = 0;
	while (start <= end) v[start++] = tmp[t++];
}


/************************************************************************/
void DoMergeSort(vector<int>& v, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		DoMergeSort(v, start, mid);
		DoMergeSort(v, mid + 1, end);
		Merge(v, start, mid, end);
	}
}

void MergeSort(vector<int>& v) {
	DoMergeSort(v, 0, v.size() - 1);
}


/************************************************************************/
/* 堆排序                                                                     
0.升序序列用大顶堆，降序序列用小顶堆。
1.将无序序列调整为一个初始的大顶堆( 从最后一个非叶子节点开始 逐层向上 构建（使该节点大于其左右孩子节点,调整过程中也要满足该原则），直至根节点)--------->这相当于一趟堆排序
2.将堆顶(此时根节点应为最大值)与堆尾元素互换，无序堆元素个数减1（无序堆元素个数为1，结束，此时已经将无序序列调整为升序序列。）
3.重复步骤1.
*/
/************************************************************************/
void DoHeapSort(vector<int>& v, int start, int end) {
	/*16 7 3 20 17 8*/
	/*
	1.将无序序列调整为大顶堆
	*/
	int first = start;

	for (int i = first; i >= 0; --i) {
		while (true) {
			int left = 2 * i + 1;
			if (left > end) break;
			if (left + 1 <= end && v[left + 1] > v[i]) {
				left += 1;
			}

			if (left <= end && v[left] > v[i]) {
				swap(v[left], v[i]);
				i= left;
			}
			else
				break;
			printf("%d ", i);
			print_arr(v);
		}

	}
	/*
	2.堆顶堆尾元素互换(堆顶元素下标永远是0)
	*/
	if(end!= 0)
		swap(v[0], v[end]);

	/*
	3.重复第一步
	*/
	if (end >= 1)
		DoHeapSort(v, (end)/2-1, end - 1);
}

void HeapSort(vector<int> &v) {
	int start = v.size() / 2 - 1;
	int end = v.size() - 1;
	DoHeapSort(v, start, end);
}
void DoHeapSort2(vector<int>& v, int start, int end) {
	/*16 7 3 20 17 8*/
	/*
	1.将无序序列调整为大顶堆
	*/
	for (int i = start; i >= 0; --i) {
		while (true) {
			int left = 2 * i + 1;
			if (left > end) break;
			if (left + 1 <= end && v[left + 1] > v[i]) {
				left += 1;
			}

			if (left <= end && v[left] > v[i]) {
				swap(v[left], v[i]);
				i = left;
			}
			else
				break;
			printf("%d ", i);
			print_arr(v);
		}
	}
}
void HeapSort2(vector<int> & v) {
	int start = v.size() / 2 - 1;
	int end = v.size() - 1;
	DoHeapSort2(v, start, end);//1.将无序序列调整为一个初始的大顶堆( 从最后一个非叶子节点开始 逐层向上 构建（使该节点大于其左右孩子节点,调整过程中也要满足该原则），直至根节点)--------->这相当于一趟堆排序
	for (int i = end; i > 0; --i) {
		swap(v[0], v[i]);//	2.堆顶堆尾元素互换(堆顶元素下标永远是0)
		DoHeapSort2(v, i/2-1, i-1);//3.重复第一步
	}
}



/*
***************************************************************************************平衡二叉树*************************************************************************************************
二叉排序树基础上增加平衡因子

*/
int main(int argc, char**argv) {
	vector<int> vv{ 16, 7, 3, 20, 17, 8 };
	vector<int> v;

	fprintf(stdout, "********************HeapSort****************************\n");
	v = vv;
	print_arr(v);
	HeapSort(v);
	print_arr(v);

	fprintf(stdout, "********************HeapSort2****************************\n");
	v = vv;
	print_arr(v);
	HeapSort2(v);
	print_arr(v);
	
	fprintf(stdout, "*****************MergeSort*******************************\n");
	v = vv;
	print_arr(v);
	MergeSort(v);
	print_arr(v);


	fprintf(stdout, "*****************QuickSort*******************************\n");
	v = vv;
	print_arr(v);
	QuickSort(v);
	print_arr(v);

	return 0;
}








