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
		//if (pMidOrder == endMidOrder)
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

给定二叉树和其中一个节点 找出中序遍历的下一个节点。
	   a
	b      c
  d   e  f   g
    h   i
*/

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

int Fibonacci(int n) {
	if (n <= 0) return 0;
	if (n == 1 || n == 2)return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
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
	}



	fprintf(stdout, "\nfrog_jump:%d\n", frog_jump(30));

	fprintf(stdout, "\Fibonacci:%d\n", Fibonacci(10));
	return 0;
}



