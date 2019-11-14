
class CBitmap {
private:
	const static unsigned int UINT_BITS = sizeof(unsigned int);
	const static unsigned int SHIFT = UINT_BITS +1;
	const static unsigned int MASK = 0x1F;
	const static unsigned int MAX_NUMBER_VALUE = (long long)(1024ll * 1024ll * 1024ll * 4ll) -1;//40亿 B、KB、MB、GB。
	const static long long count = ((long long)MAX_NUMBER_VALUE + 1) / UINT_BITS / 8;
		  static unsigned int ARR[count];// MAX_NUMBER_VALUE / UINT_BITS个int的数组。  可以存放 MAX_NUMBER_VALUE / UINT_BITS * 8(bit)

public:

	//i >> SHIFT 定位到哪个buket，在buket内再偏移到对应的bit位置。
	void set(unsigned int i) {
		ARR[i >> SHIFT] |= (1 << (i & MASK));
	}

	int test(unsigned int i) {
		return ARR[i >> SHIFT] & ( 1 << (i & MASK));
	}

	void clear(unsigned int i) {
		ARR[i >> SHIFT] &= (~(1 << (i & MASK)));
	}
};

#include <string.h>
#include <vector>

void all_range(std::string str, int k) {


	for (int i = k; i < str.length(); ++i) {
		char tmp = str[i];
		str[i] = str[k];
		str[k] = tmp;

		all_range(str,  k + 1);

		tmp = str[k];
		str[k] = str[i];
		str[i] = tmp;
		
	}

	if (k == str.length())
		fprintf(stdout, "%s\n", str.c_str());
}

#include <unordered_map>

int main(int argc, char** argv) {


	int a = sizeof(int);
	int b = sizeof(long);
	int c = sizeof(long long);
	CBitmap cb;

	char str[] = "abc";
	int len = strlen(str);
	char str1[10] = { 0x01 };
	memset(str1, 0x01, sizeof str1);
	strcpy(str1, str);



	all_range(str, 0);




	

	return 0;
}


//http://wuchong.me/blog/2014/07/28/permutation-and-combination-realize/

//https://blog.csdn.net/morewindows/article/details/7370155 
// https://blog.csdn.net/qq_42552533/article/details/88606550
//https://blog.csdn.net/jiaobuchong/article/details/85369970
