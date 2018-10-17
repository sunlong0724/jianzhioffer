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

int main(int argc, char** argv) {

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



