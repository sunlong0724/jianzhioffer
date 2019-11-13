
class CBitmap {
private:
	const static unsigned int UINT_BITS = sizeof(unsigned int);
	const static unsigned int SHIFT = UINT_BITS +1;
	const static unsigned int MASK = 0x1F;
	const static unsigned int MAX_NUMBER_VALUE = 1024 * 1024 * 1024;//10��
		  static unsigned int ARR[MAX_NUMBER_VALUE / UINT_BITS];//���Դ�� MAX_NUMBER_VALUE / UINT_BITS * 8(bit)

public:

	//i >> SHIFT ��λ���ĸ�buket����buket����ƫ�Ƶ���Ӧ��bitλ�á�
	void set(unsigned int i) {
		ARR[i >> SHIFT] |= (1 << (i & MASK));
	}

	int test(unsigned int i) {
		return ARR[i >> SHIFT] & ( 1 << (i & MASK));
	}

	void clear(unsigned int i) {
		ARR[i >> SHIFT] & ~(1 << (i & MASK));
	}
};