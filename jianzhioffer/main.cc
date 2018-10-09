#include <stdio.h>
#include <stack>
#include <vector>


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

	while (!s.empty()) {
		if (root) root = root->left;
		if (root) {
			s.push(root);
		}else{
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
	}

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

	s.push(root);

	while (!s.empty()) {
		root = root->left;

		if (root) {
			s.push(root);
		}
		else {
			while (!s.empty()) {
				BinaryTreeNode* node = s.top();
				//s.pop();
				if (node) {
					if (node->left && node->right) {
						s.pop();
					}

					root = node->right;
					if (root) {
						s.push(root);
						break;
					}
					else {
						s.pop();
						v.push_back(node);
						continue;
					}
				}
			}
		}



	}

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






int main(int argc, char** argv) {

	BinaryTreeNode tree[] = { {10, &tree[1], &tree[2]},{ 6, &tree[3], &tree[4] },{ 14, &tree[5], &tree[6] },{ 4, NULL,NULL },{ 8,  NULL,NULL },{ 12, NULL,NULL },{ 16, NULL,NULL }};
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
	return 0;
}