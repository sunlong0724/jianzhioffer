/*
һ�������㷨
	1.��ķ����---��ʱ����
	2.ð��
	3.ֱ��ѡ������
	4.ֱ�Ӳ�������
	5.��������
	6.�鲢����
	7.������

�������ݽṹ
	1.��ȫ����������
	2.���������������򡢺������(ѭ�����ݹ�ʵ�֣������������������ȡ�������ȱ���
	3.�������ĸ߶�
	4.ƽ����������������롢ɾ��
	5.�����
	6.b+ b-��---��ʱ����

���������㷨
	1.̰���㷨
	2.��̬�滮

�ġ����߳����

�塢����ģ��
	1.TPC/IPЭ��ģ�� ��������

��������������
	1.ģ��
	2.type_traits

�ߡ�Windowsƽ̨���
	1.Windows��Ϣ���л���

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


/************************************************************************************************���򷽷�******************************************************************************************/


/************************************************************************/
/* ��������                 
0.ѡ��һ����ŦԪ�أ�Ϊ���ҵ��������е���ȷλ�ã�ʹ�����Ԫ�ر���С���ұ�Ԫ�ر����
1.�ظ��������衣
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
/*�鲢����
0.���������зֽ�Ϊ������
1.������������
2.������õ��������������й鲢
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
/* ������                                                                     
0.���������ô󶥶ѣ�����������С���ѡ�
1.���������е���Ϊһ����ʼ�Ĵ󶥶�( �����һ����Ҷ�ӽڵ㿪ʼ ������� ������ʹ�ýڵ���������Һ��ӽڵ�,����������ҲҪ�����ԭ�򣩣�ֱ�����ڵ�)--------->���൱��һ�˶�����
2.���Ѷ�(��ʱ���ڵ�ӦΪ���ֵ)���βԪ�ػ����������Ԫ�ظ�����1�������Ԫ�ظ���Ϊ1����������ʱ�Ѿ����������е���Ϊ�������С���
3.�ظ�����1.
*/
/************************************************************************/
void DoHeapSort(vector<int>& v, int start, int end) {
	/*16 7 3 20 17 8*/
	/*
	1.���������е���Ϊ�󶥶�
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
	2.�Ѷ���βԪ�ػ���(�Ѷ�Ԫ���±���Զ��0)
	*/
	if(end!= 0)
		swap(v[0], v[end]);

	/*
	3.�ظ���һ��
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
	1.���������е���Ϊ�󶥶�
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
	DoHeapSort2(v, start, end);//1.���������е���Ϊһ����ʼ�Ĵ󶥶�( �����һ����Ҷ�ӽڵ㿪ʼ ������� ������ʹ�ýڵ���������Һ��ӽڵ�,����������ҲҪ�����ԭ�򣩣�ֱ�����ڵ�)--------->���൱��һ�˶�����
	for (int i = end; i > 0; --i) {
		swap(v[0], v[i]);//	2.�Ѷ���βԪ�ػ���(�Ѷ�Ԫ���±���Զ��0)
		DoHeapSort2(v, i/2-1, i-1);//3.�ظ���һ��
	}
}



/*
***************************************************************************************ƽ�������*************************************************************************************************
��������������������ƽ������

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








