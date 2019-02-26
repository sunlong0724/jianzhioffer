
#include <vector>
using namespace std;
/************************************************************************
��̬�滮�㷨��������ʽ
���Զ����µı���¼��
���Ե����ϡ�
/* Dynamic Program sample                                                                     */
/************************************************************************/
/*
쳲��������� 1 1 2 3 5 8 13 21 34..
*/
int Fib(int n, vector<int>& v) {
	if (n <= 2)return v[n]=1;
	if (v[n] != 0x00) return v[n];
	else
		return v[n] = Fib(n - 1, v) + Fib(n - 2, v);
}

int FibonacciDy(int n) {
	if (n <= 0)return 0;
	vector<int> v(n + 1, 0x00);
	

	int res = Fib(n, v);
	//for (auto vv : v) {
	//	fprintf(stdout, "%d,", vv);
	//}

	return res;
}

int FibonacciDy2(int n) {

	if (n <= 2)return 1;
	int res = 0;
	int sum1 = 1, sum2 = 1;
	for (int i = 3; i <= n; ++i) {
		res = 0;

		res += sum1;
		res += sum2;
		
		sum1 = sum2;
		sum2 = res;
	}
	return res;
}

#include <algorithm>
int cut(int n) {
	static int price[] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int result = 0;
	for (int i = 1; i <= n; ++i) {
		result = std::max(result, price[i] + cut(n - i));
	}
	return result;
}

int cut2Memo(int n, vector<int>& r) {
	static int price[] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int result = 0;
	if (r[n] != 0x00) 
		return r[n];

	for (int i = 1; i <= n; ++i) {
		result = std::max(result, price[i] + cut2Memo(n - i, r));
	}
	return r[n] = result;
}
int cut2(int n) {
	
	vector<int> r(n + 1, 0x00);
	return cut2Memo(n, r);
}


int cutButom2UpDy(int n) {
	vector<int> r(n + 1, 0x00);
	static int price[] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int q = -1;
	for (int i = 1; i <= n; ++i) {
		q = -1;
		for (int j = 0; j <= i; ++j) {
			q = std::max(q, price[j] + r[i - (j)]);
		}
		r[i] = q;
	}

	return r[n];
}

int cut3(int n) {
	return cutButom2UpDy(n);
}



/************************************************************************/
/* 
0-1 �������⣺���� n ����Ʒ��һ������Ϊ C �ı�������Ʒ i �������� wi�����ֵΪ vi ��
�ʣ�Ӧ�����ѡ��װ�뱳������Ʒ��ʹ��װ�뱳���е���Ʒ���ܼ�ֵ���

0-1�������⡣��ʹ�ö�̬�滮�㷨���0-1��������ʱ��ʹ�ö�ά����m[i][j]�洢����ʣ������Ϊj����ѡ��ƷΪi��i+1��������nʱ0-1�������������ֵ������
��ֵ����v = {8, 10, 6, 3, 7, 2}��
��������w = {4, 6, 2, 2, 5, 1}��
��������C = 12

����취������һ�� ��СΪ  m[n][c] �Ķ�ά���飬m[ i ][ j ] ��ʾ ����Ե� i ����Ʒ���ұ�������Ϊ  j ʱ���ܻ�õ�����ֵ ����ô���ǿ��Ժ����׷����ó� m[i][j] �ļ��㷽����
��1��. j < w[i] ���������ʱ�򱳰����������Է��µ� i ����Ʒ��ֻ��ѡ����m[ i ][ j ] = m[ i-1 ][ j ]
��2��. j>=w[i] ���������ʱ�����������Է��µ� i ����Ʒ�����Ǿ�Ҫ�����������Ʒ�Ƿ��ܻ�ȡ����ļ�ֵ��
�����ȡ��m[ i ][ j ]=m[ i-1 ][ j-w[ i ] ] + v[ i ]�� �����m[ i-1 ][ j-w[ i ] ]ָ�ľ��ǿ�����i-1����Ʒ����������Ϊj-w[i]ʱ������ֵ��Ҳ���൱��Ϊ��i����Ʒ�ڳ���w[i]�Ŀռ䡣
������ã�m[ i ][ j ] = m[ i-1 ][ j ] , ͬ��1��
�������û��ǲ��ã���Ȼ�ǱȽ�������������ּ�ֵ���
״̬ת�Ʒ��̣�
if(j >= w[i]) m[i][j]=max(m[i-1][j],m[i-1][j-w[i]]+v[i])
else m[i][j] = m[i-1][j]

*/
/************************************************************************/

void bags() {
	const int N = 15;
	int v[N] = {0, 8, 10, 6, 3, 7, 2 };
	int w[N] = { 0,  4, 6, 2, 2, 5, 1 };

	int m[N][N] = { 0 };
	int n = 6, c = 12;

	int i = 0;
	int k = 0;
	for (i = 1; i <= n; ++i) {

		for (int j = 1; j <= c; ++j) {

			if (j >= w[i]) {
				k= std::max(m[i - 1][j], m[i - 1][j - w[i]] + v[i]);
				m[i][j] = k;
			}
			else {
				m[i][j] = m[i - 1][j];
			}
		}
	}

	for (i = 1; i <= n; ++i) {

		for (int j = 1; j <= c; ++j) {
			fprintf(stdout, "%d,", m[i][j]);
		}
		fprintf(stdout, "\n");
	}

	int x[N] = { 0 };
	for (int i = n; i > 1; i--)
	{
		if (m[i][c] == m[i - 1][c])
			x[i] = 0;
		else
		{
			x[i] = 1;
			c -= w[i];

		}
	}
	x[1] = (m[1][c] > 0) ? 1 : 0;

	for (int i = 1; i <= n; ++i) {
		if (1 == x[i])
			fprintf(stdout, "%d,", i);
	}
	fprintf(stdout, "\n");

}


int main56(int argc, char** argv) {
	fprintf(stdout, "FibonacciDy:%d\n", FibonacciDy(9));
	fprintf(stdout, "FibonacciDy2:%d\n", FibonacciDy2(9));


	fprintf(stdout, "cut:%d\n", cut(4));
	fprintf(stdout, "cut2:%d\n", cut2(4));
	fprintf(stdout, "cut3:%d\n", cut3(4));


	fprintf(stdout, "\n*******************bags****************\n");
	bags();


	return 0;
}