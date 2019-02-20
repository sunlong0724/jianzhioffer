
#include <vector>
using namespace std;
/************************************************************************/
/* Dynamic Program sample                                                                     */
/************************************************************************/
/*
ì³²¨ÄÇÆõÊýÁÐ 1 1 2 3 5 8 13 21 34..
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



int main(int argc, char** argv) {
	fprintf(stdout, "FibonacciDy:%d\n", FibonacciDy(9));
	fprintf(stdout, "FibonacciDy2:%d\n", FibonacciDy2(9));


	fprintf(stdout, "cut:%d\n", cut(4));
	fprintf(stdout, "cut2:%d\n", cut2(4));
	fprintf(stdout, "cut3:%d\n", cut3(4));
	return 0;
}