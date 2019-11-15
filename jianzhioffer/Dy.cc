
#include <vector>
using namespace std;
/************************************************************************
动态规划算法的两种形式
①自顶向下的备忘录法
②自底向上。
/* Dynamic Program sample                                                                     */
/************************************************************************/
/*
斐波那契数列 1 1 2 3 5 8 13 21 34..
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
0-1 背包问题：给定 n 种物品和一个容量为 C 的背包，物品 i 的重量是 wi，其价值为 vi 。
问：应该如何选择装入背包的物品，使得装入背包中的物品的总价值最大？

0-1背包问题。在使用动态规划算法求解0-1背包问题时，使用二维数组m[i][j]存储背包剩余容量为j，可选物品为i、i+1、……、n时0-1背包问题的最优值。绘制
价值数组v = {8, 10, 6, 3, 7, 2}，
重量数组w = {4, 6, 2, 2, 5, 1}，
背包容量C = 12

解决办法：声明一个 大小为  m[n][c] 的二维数组，m[ i ][ j ] 表示 在面对第 i 件物品，且背包容量为  j 时所能获得的最大价值 ，那么我们可以很容易分析得出 m[i][j] 的计算方法，
（1）. j < w[i] 的情况，这时候背包容量不足以放下第 i 件物品，只能选择不拿m[ i ][ j ] = m[ i-1 ][ j ]
（2）. j>=w[i] 的情况，这时背包容量可以放下第 i 件物品，我们就要考虑拿这件物品是否能获取更大的价值。
如果拿取，m[ i ][ j ]=m[ i-1 ][ j-w[ i ] ] + v[ i ]。 这里的m[ i-1 ][ j-w[ i ] ]指的就是考虑了i-1件物品，背包容量为j-w[i]时的最大价值，也是相当于为第i件物品腾出了w[i]的空间。
如果不拿，m[ i ][ j ] = m[ i-1 ][ j ] , 同（1）
究竟是拿还是不拿，自然是比较这两种情况那种价值最大。
状态转移方程：
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


//TODO:
//https://blog.csdn.net/huanhuan_coder/article/details/79099597

//参考:
//https://www.zhihu.com/question/2399518//
//https://www.luogu.org/blog/pks-LOVING/junior-dynamic-programming-dong-tai-gui-hua-chu-bu-ge-zhong-zi-xu-lie

//https://www.zhihu.com/question/39948290?sort=created


//例题1 凑出某个金额w，需要用到尽量少的钞票
//例题2 DAG最短路 给定一个城市的地图，所有的道路都是单行道，而且不会构成环。每条道路都有过路费，问您从S点到T点花费的最少费用。
//例题3 最长上升子序列
//例题4 挖金矿
