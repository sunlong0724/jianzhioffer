#include <stdio.h>
#include <stack>
#include <vector>
#include <exception>

typedef struct BinaryTreeNode{
	int val;
	BinaryTreeNode* left;
	BinaryTreeNode* right;
}BinaryTreeNode;

typedef void (*process_func_ptr)(BinaryTreeNode*);

void printf_node(BinaryTreeNode* node) {
	if (node)
		fprintf(stdout, "%d ", node->val);
}

/*
二叉树的先序 中序 后序 的递归和循环实现方式

	10
  6		 14
4  8   12   16

*/
void preOrder2(BinaryTreeNode* root, process_func_ptr func_ptr) {
	std::stack<BinaryTreeNode*> s;
	std::vector<BinaryTreeNode*> v;
	if (!root) {
		return;
	}

	v.push_back(root);
	s.push(root);
	while (!s.empty()) {
		if (root)
			root = root->left;

		if (root == NULL) {
			while (!s.empty()) {
				BinaryTreeNode* node = s.top();
				s.pop();
				root = node->right;
				if (root == NULL) {
					continue;
				}
				else {
					v.push_back(root);
					s.push(root);
					break;
				}
			}
		}
		else {
			v.push_back(root);
			s.push(root);
		}
	}


	for (int i = 0; i < v.size(); ++i) {
		func_ptr(v[i]);
	}



}
void preOrder(BinaryTreeNode* root, process_func_ptr func_ptr) {
	if (root == NULL) {
		return;
	}
	if (func_ptr) {
		func_ptr(root);
	}
	preOrder(root->left, func_ptr);
	preOrder(root->right, func_ptr);
}
void midOrder(BinaryTreeNode* root, process_func_ptr func_ptr) {
	if (root == NULL) {
		return;
	}
	midOrder(root->left, func_ptr);
	if (func_ptr) {
		func_ptr(root);
	}
	midOrder(root->right, func_ptr);
}
void midOrder2(BinaryTreeNode* root, process_func_ptr func_ptr) {
	if (root == NULL) {
		return;
	}

	std::stack<BinaryTreeNode*> s;
	std::vector<BinaryTreeNode*> v;

	s.push(root);
	do 
	{
		if (root->left) {
			root = root->left;
			s.push(root);
		}
		else {
			while (!s.empty()) {
				BinaryTreeNode* node = s.top();
				s.pop();
				v.push_back(node);

				root = node->right;
				if (root) {
					s.push(root);
					break;
				}
				else continue;
			}
		}


	} while (!s.empty());

	for (int i = 0; i < v.size(); ++i) {
		func_ptr(v[i]);
	}

}
void postOrder2(BinaryTreeNode* root, process_func_ptr func_ptr) {
	if (root == NULL) {
		return;
	}

	std::stack<BinaryTreeNode*> s;
	std::vector<BinaryTreeNode*> v;

	do {
		while (root) {
			s.push(root);
			root = root->left;
		}

		int flag = 1;
		BinaryTreeNode* last = NULL;
		while (!s.empty() && flag == 1) {
			BinaryTreeNode* node = s.top();

			if (node->right == last) {
				s.pop();
				v.push_back(node);
				last = node;
			}
			else {
				root = node->right;
				flag = 0;
			}

		}



	} while (!s.empty());


	for (int i = 0; i < v.size(); ++i) {
		func_ptr(v[i]);
	}

}
void postOrder(BinaryTreeNode* root, process_func_ptr func_ptr) {
	if (root == NULL) {
		return;
	}
	postOrder(root->left, func_ptr);
	postOrder(root->right, func_ptr);
	if (func_ptr) {
		func_ptr(root);
	}
}


/*
层次遍历,并分行
*/

void level_traversal(BinaryTreeNode* root) {
	if (root == NULL)return;
	std::stack<BinaryTreeNode*> s,s2;
	std::stack<BinaryTreeNode*>* p1 = &s,*p2=&s2, *tmp;
	p1->push(root);

	int height =-1;

	do {
	
		while (!p1->empty()) {
			BinaryTreeNode* node = p1->top();
			p1->pop();
			fprintf(stdout, "%d ", node->val);
			if (node->right) p2->push(node->right);
			if (node->left) p2->push(node->left);

	
		}

		tmp = p1;
		p1 = p2;
		p2 = tmp;
		
		++height;
		fprintf(stdout, " \n");

	} while (!p1->empty());
}
/*
求二叉树的高度 3种实现方式
递归
后序遍历 栈的最大长度
层序遍历栈的长度
*/

int tree_height(BinaryTreeNode* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 0;

	int l_h = 1 + tree_height(root->left);
	int r_h = 1 + tree_height(root->right);

	return l_h > r_h ? l_h : r_h;
}
int tree_height2(BinaryTreeNode* root) {
	std::stack<BinaryTreeNode*> s;
	std::vector<BinaryTreeNode*> v;
	if (root == NULL)
		return 0;

	int height = 0;
	int cnt = -1;
	do{
		while(root) {
			s.push(root);
			root = root->left;
			++cnt;
		}


		if (cnt > height) height = cnt;
		BinaryTreeNode* last = NULL;// 记录上次访问的节点
		int flag = 1;//需要访问站内节点
		while (!s.empty() && flag == 1) {
			BinaryTreeNode* node = s.top();
			if (node->right == last) {
				s.pop();
				last = node;
				--cnt;
				//fprintf(stdout, "#%d ", node->val);
				v.push_back(node);
			}
			else {
				root = node->right;
				flag = 0;//需要遍历该子树的节点以添加到栈里
			}
		}

	}while (!s.empty());

	for (auto a : v) {
		fprintf(stdout, "%d ", a->val);
	}


	return height;

}
int tree_height3(BinaryTreeNode* root) {
	std::stack<BinaryTreeNode*> s, s2, *tmp, *p,*p2;

	if (root == NULL) {
		return 0;
	}

	int height = -1;
	p = &s;
	p2 = &s2;
	p->push(root);

	do 
	{
		while (!p->empty())
		{
			BinaryTreeNode* node = p->top();
			p->pop();

			fprintf(stdout, "%d ", node->val);
			
			if (node->right)	p2->push(node->right);
			if (node->left)		p2->push(node->left);
		}

		tmp = p;
		p = p2;
		p2 = tmp;

		height++;
		fprintf(stdout, " #%d# \n ", height);

	} while (!p->empty());
}

/*
二叉搜索树
*/

bool bst(BinaryTreeNode* root, int key) {
	if (root == NULL)
		return false;

	if (root->val == key)
		return true;
	else if (key < root->val) {
		return bst(root->left, key);
	}else {
		return bst(root->right, key);
	}
}

/*
先序1 2 4 7 3 5 6 8
中序4 7 2 1 5 3 8 6
*/
BinaryTreeNode* do_build_tree(int* startPreOrder, int* endPreOrder, int* startMidOrder, int* endMidOrder) {

	BinaryTreeNode* root = new BinaryTreeNode;
	root->left = root->right = NULL;
	root->val = startPreOrder[0];

	if (startPreOrder == endPreOrder) {
		if (startMidOrder == endMidOrder) {
			return root;
		}
	}

	int* pMidOrder = startMidOrder;
	while (pMidOrder != endMidOrder) {
		if (root->val == *pMidOrder) {
			break;
		}

		pMidOrder++;
	}

	int leftLength = 0;
	if (root->val == *pMidOrder) {
		leftLength = pMidOrder - startMidOrder;
	}
	else {
		if (pMidOrder == endMidOrder)
		{
			throw std::exception("not found!\n");
		}
	}

	if (leftLength > 0) {
		root->left = do_build_tree(startPreOrder + 1, startPreOrder + leftLength, startMidOrder, pMidOrder-1);
	}

	if (endMidOrder - pMidOrder > 0) {
		root->right = do_build_tree(startPreOrder + leftLength + 1, endPreOrder, pMidOrder + 1, endMidOrder);
	}

	return root;
}
BinaryTreeNode* build_tree(int* startPreOrder, int* startMidOrder, int length) {
	if (startPreOrder == NULL || startMidOrder == NULL || length <= 0) {
		return NULL;
	}

	return do_build_tree(startPreOrder, startPreOrder + length - 1, startMidOrder, startMidOrder + length - 1);
}

/*
中序 d b h e i a f c g

给定二叉树和其中一个节点 找出中序遍历的下一个节点(每个节点包含一个指向父节点的指针)。
	   a
	b      c
  d   e  f   g
    h   i
*/
typedef struct BinaryTreeNode2{
	char	val;
	struct BinaryTreeNode2* left;
	struct BinaryTreeNode2* right;
	struct BinaryTreeNode2* parent;
}BinaryTreeNode2;

BinaryTreeNode2* getNextNode(BinaryTreeNode2* pNode) {
	if (pNode == NULL)return NULL;

	BinaryTreeNode2* pNext = NULL;
	//1.该节点有右子树，则其右子树的最左节点即为中序遍历的next节点
	if (pNode->right != NULL) {
		pNext = pNode->right;
		while (pNext->left) {
			pNext = pNext->left;
		}
	}
	else {//2.1. 该节点无右子树，且其为其父节点的左子节点，其父节点即为中序遍历的next节点
		if (pNode == pNode->parent->left) {
			pNext = pNode->parent;
		}
		else {//2.2 该节点为无右子树，且其为其父节点的右子节点，则其祖父节点中的第一个为其父节点的左子节点的 节点 为 其 next节点。
			pNext = pNode->parent;
			do{
				if (pNext && pNext == pNext->parent->left)
					break;
				pNext = pNext->parent;
			} while (pNext);
			if (pNext && pNext == pNext->parent->left)
				pNext = pNext->parent;
		}

	}

	return pNext;
}


/*
一只青蛙一次可以跳1级台阶，也可以跳2级台阶。求该青蛙跳上一个n级的台阶总共有多少种跳法。
n		1	2		3				4
f(n)	1	2	f(2)+f(1)=3		f(3)+f(2)
*/

int frog_jump(int n) {
	if (n <= 0)return 0;
	if (n == 1 || n == 2) return n;
	return frog_jump(n - 1) + frog_jump(n - 2);
}

/*
斐波那契数列 1 1 2 3 5 8 13 21 ...
*/
int Fibonacci(int n) {
	if (n <= 0) return 0;
	if (n == 1 || n == 2)return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int Fibonacci2(int n) {
	int result[] = { 0, 1,1 };
	if (n <= 0)return result[0];
	else if (n <= 2) result[n];
	else {

		int FibonacciOne = 1;
		int FibonacciTwo = 0;
		int ret = 0;

		for (int i = 1; i < n; ++i) {
			ret = FibonacciOne + FibonacciTwo;
			FibonacciTwo = FibonacciOne;
			FibonacciOne = ret;
		}
		return ret;
	}

}

int main0000(int argc, char** argv) {

	{
		BinaryTreeNode tree[] = { {10, &tree[1], &tree[2]},{ 6, &tree[3], &tree[4] },{ 14, &tree[5], &tree[6] },{ 4, NULL,NULL },{ 8,  NULL,NULL },{ 12, NULL,NULL },{ 16, NULL,NULL } };
		fprintf(stdout, "\n");
		preOrder(tree, printf_node);
		fprintf(stdout, "\n");
		midOrder(tree, printf_node);
		fprintf(stdout, "\n");
		postOrder(tree, printf_node);
		fprintf(stdout, "\n");
		preOrder2(tree, printf_node);
		fprintf(stdout, "\n");
		midOrder2(tree, printf_node);
		fprintf(stdout, "\n");
		postOrder2(tree, printf_node);

		fprintf(stdout, "\n build\n");

		int preOrderArr[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
		int midOrderArr[] = { 4, 7, 2, 1, 5 ,3, 8, 6 };
		BinaryTreeNode* tree2 = build_tree(preOrderArr, midOrderArr, sizeof midOrderArr / sizeof(int));
		preOrder(tree2, printf_node);
		fprintf(stdout, "\n");
		midOrder(tree2, printf_node);

		fprintf(stdout, "\ntree_height:tree:%d, tree2:%d\n", tree_height(tree), tree_height(tree2));
		//fprintf(stdout, "\ntree_height2:tree:%d, tree2:%d\n", tree_height2(tree), tree_height2(tree2));
		int h1 = tree_height2(tree);
		int h2 = tree_height2(tree2);
		fprintf(stdout, "\ntree_height2:tree:%d, tree2:%d\n", h1, h2);

		h1 = tree_height3(tree);
		h2 = tree_height3(tree2);
		fprintf(stdout, "\ntree_height3:tree:%d, tree2:%d\n", h1, h2);

		fprintf(stdout, "\n\n");
		level_traversal(tree2);
		fprintf(stdout, "\n\n");
	}



	fprintf(stdout, "\nfrog_jump:%d\n", frog_jump(30));

	fprintf(stdout, "\nFibonacci:%d\n", Fibonacci(30));

	fprintf(stdout, "\nFibonacci2:%d\n", Fibonacci2(30));

	fprintf(stdout, "\n##################################\n");

	/* a
	b      c
  d   e  f   g
	h   i
	*/
	BinaryTreeNode2 tree_c[] = { {'a',&tree_c[1],&tree_c[2],NULL },{ 'b',&tree_c[3],&tree_c[4],&tree_c[0] },{ 'c',&tree_c[5],&tree_c[6],&tree_c[0] },
									{ 'd',NULL,NULL,&tree_c[1] },{ 'e',&tree_c[7],&tree_c[8],&tree_c[1] },{ 'f',NULL,NULL,&tree_c[2] },{ 'g',NULL,NULL,&tree_c[2] },
									{ 'h',NULL,NULL,&tree_c[4] },{ 'i',NULL,NULL,&tree_c[4] }
								};

	BinaryTreeNode2* node = getNextNode(&tree_c[8]);
	if (node) {
		fprintf(stdout, "getNextNode %c\n", node->val);
	}
	else {
		fprintf(stdout, "getNextNode null\n");
	}

	return 0;
}

#include <vector>
using namespace std;
bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	stack<int> pushS;
	int i = 0, j = 0;
	for (; i < popV.size(); ++i) {
		if ( !pushS.empty() && popV[i] == pushS.top()) {
			pushS.pop();
			continue;
		}
		for (; j < pushV.size(); ++j) {
			pushS.push(pushV[j]);
			printf("%d,%d----> %d,%d\n", i,j,popV[i], pushS.top());
			if (popV[i] == pushS.top()) {
				
				pushS.pop();
				++j;
				break;
			}
		}
	}

	printf("####%d,%d---->\n", i, j);
	return pushS.empty();
}






bool DoVerifySquenceOfBST(vector<int>& v, int start, int end) {
	if (start == end) return true;
	int i = start;
	int root_val = v[end];
	for (; i < end; ++i) {
		if (v[i] > root_val) {
			break;
		}
	}

	for (int j = i; j < end; ++j) {
		if (v[j] < root_val) {
			return false;
		}
	}

	bool left = true, right = true;

	if (i > start)
		left = DoVerifySquenceOfBST(v, start, i - 1);

	if (i < end - 1)
		right = DoVerifySquenceOfBST(v, i, end - 1);

	return left && right;

}

//后序遍历序列最后一个节点即为树的根节点
bool VerifySquenceOfBST(vector<int> v) {
	if (v.size() == 0) return false;

	return DoVerifySquenceOfBST(v, 0, v.size() - 1);
}

void DoPermutation(vector<string>& v, string& str, int start) {
	if (start >= str.size()) {
		v.push_back(str);
		return;
	}
	for (int i = start; i < str.size(); ++i) {
		char t = str[start];
		str[start] = str[i];
		str[i] = t;

		DoPermutation(v, str, start + 1);

		t = str[i];
		str[i] = str[start];
		str[start] = t;
	}
}

vector<string> Permutation(string str) {
	vector<string> v;
	if (str.size() == 0) return v;
	DoPermutation(v, str, 0);
	return v;
}



void Merge0(vector<int> &v, vector<int>&res, int left_start, int left_end,
	int right_start, int right_end) {
	int i = left_start;
	int j = right_start;
	int t = 0;

	while (i <= left_end && j <= right_end) {
		if (v[i] <= v[j]) {
			res[t++] = v[i++];
		}
		else {
			res[t++] = v[j++];
		}
	}

	while (i <= left_end) res[t++] = v[i++];
	while (j <= right_end) res[t++] = v[j++];

	t = 0;
	while (left_start <= right_end) v[left_start++] = res[t++];

}


void Merge(vector<int> &v, vector<int>&res, int left_start, int left_end,
	int right_start, int right_end) {
	int i = left_end;
	int j = right_end;

	int t = right_end;

	while (i >= left_start && j >= right_start) {
		if (v[i] > v[j]) {
			res[t--] = v[i--];

		}
		else {
			res[t--] = v[j--];
		}
	}

	while (i >= left_start) res[t--] = v[i--];
	while (j >= right_start) res[t--] = v[j--];
	
	t = left_start;
	i = left_start;
	while (i >= right_end) v[i++] = res[t++];

	/*
	t = right_end;
	i = right_end;
	while (i >= left_start) v[i--] = res[t--];
	*/
	int ss = -1;

}

void MergeSort(vector<int>& v, vector<int>& res, int start, int end) {

	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(v, res,start, mid);
		MergeSort(v, res, mid + 1, end);
		Merge0(v, res, start, mid, mid + 1, end);
	}
}



int main66(int argc, char** argv) {

	/*int a = -3;
	unsigned int b = a;
	unsigned int c = (unsigned int)a;

	printf("%d,%d,%d\n", a, b, c);

	vector<int> v1 = { 1, 2, 3, 4, 5 };
	vector<int> v2 = { 4, 5, 3, 2, 1 };

	bool res = IsPopOrder(v1, v2);


	vector<int> v = { 7,6,4,5 };

	bool res = VerifySquenceOfBST(v);
	

	string str = "aa";
	vector<string> res = Permutation(str);
	for (int i = 0; i < res.size(); ++i) {
		printf("%s\n", res[i].c_str());
	}


	int arr[sizeof (char)] = { 0 };
	int i = sizeof arr;
	*/

	vector<int> arr = { 1,3,2,5,4,7,6,8 };
	vector<int> res(arr.size(), 0x00);

	MergeSort(arr, res, 0, arr.size() -1);

	printf("\n arr:");
	for (int i = 0; i < arr.size(); ++i) {
		printf("%d,", arr[i]);
	}


	printf("\n result:");
	for (int i = 0; i < res.size(); ++i) {
		printf("%d,", res[i]);
	}

	printf("\n");
	return 0;
}

/*

链接：https://www.nowcoder.com/questionTerminal/fe6b651b66ae47d7acce78ffdd9a96c7
来源：牛客网

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
public class Solution {
	public ArrayList<String> Permutation(String str) {
		List<String> resultList = new ArrayList<>();
		if (str.length() == 0)
			return (ArrayList)resultList;
		//递归的初始值为（str数组，空的list，初始下标0）
		fun(str.toCharArray(), resultList, 0);
		Collections.sort(resultList);
		return (ArrayList)resultList;
	}

	private void fun(char[] ch, List<String> list, int i) {
		//这是递归的终止条件，就是i下标已经移到char数组的末尾的时候，考虑添加这一组字符串进入结果集中
		if (i == ch.length - 1) {
			//判断一下是否重复
			if (!list.contains(new String(ch))) {
				list.add(new String(ch));
				return;
			}
		}
		else {
			//这一段就是回溯法，这里以"abc"为例

			//递归的思想与栈的入栈和出栈是一样的,某一个状态遇到return结束了之后，会回到被调用的地方继续执行

			//1.第一次进到这里是ch=['a','b','c'],list=[],i=0，我称为 状态A ，即初始状态
			//那么j=0，swap(ch,0,0)，就是['a','b','c']，进入递归，自己调自己，只是i为1，交换(0,0)位置之后的状态我称为 状态B 
			//i不等于2，来到这里，j=1，执行第一个swap(ch,1,1)，这个状态我称为 状态C1 ,再进入fun函数，此时标记为T1，i为2，那么这时就进入上一个if，将"abc"放进list中
			/////////////-------》此时结果集为["abc"]

			//2.执行完list.add之后，遇到return，回退到T1处，接下来执行第二个swap(ch,1,1)，状态C1又恢复为状态B
			//恢复完之后，继续执行for循环，此时j=2,那么swap(ch,1,2),得到"acb"，这个状态我称为C2,然后执行fun，此时标记为T2,发现i+1=2,所以也被添加进结果集，此时return回退到T2处往下执行
			/////////////-------》此时结果集为["abc","acb"]
			//然后执行第二个swap(ch,1,2)，状态C2回归状态B,然后状态B的for循环退出回到状态A

			//             a|b|c(状态A)
			//               |
			//               |swap(0,0)
			//               |
			//             a|b|c(状态B)
			//             /  \
			            //   swap(1,1)/    \swap(1,2)  (状态C1和状态C2)
//           /      \
            //         a|b|c   a|c|b

//3.回到状态A之后，继续for循环，j=1,即swap(ch,0,1)，即"bac",这个状态可以再次叫做状态A,下面的步骤同上
/////////////-------》此时结果集为["abc","acb","bac","bca"]

//             a|b|c(状态A)
//               |
//               |swap(0,1)
//               |
//             b|a|c(状态B)
//             /  \
            //   swap(1,1)/    \swap(1,2)  (状态C1和状态C2)
//           /      \
            //         b|a|c   b|c|a

//4.再继续for循环，j=2,即swap(ch,0,2)，即"cab",这个状态可以再次叫做状态A，下面的步骤同上
/////////////-------》此时结果集为["abc","acb","bac","bca","cab","cba"]

//             a|b|c(状态A)
//               |
//               |swap(0,2)
//               |
//             c|b|a(状态B)
//             /  \
            //   swap(1,1)/    \swap(1,2)  (状态C1和状态C2)
//           /      \
            //         c|b|a   c|a|b

//5.最后退出for循环，结束。

			for (int j = i; j < ch.length; j++) {
				swap(ch, i, j);
				fun(ch, list, i + 1);
				swap(ch, i, j);
			}
		}
	}

	//交换数组的两个下标的元素
	private void swap(char[] str, int i, int j) {
		if (i != j) {
			char t = str[i];
			str[i] = str[j];
			str[j] = t;
		}
	}
}

*/