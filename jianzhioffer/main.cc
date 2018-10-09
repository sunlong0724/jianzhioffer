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
ÏÈÐò1 2 4 7 3 5 6 8
ÖÐÐò4 7 2 1 5 3 8 6
*/

BinaryTreeNode* build_tree(int* preOrder, int preOrderLength, int* midOrder, int midOrderLength) {
	if (preOrder == NULL || midOrder == NULL || preOrderLength != midOrderLength || preOrderLength == 0 || midOrderLength == 0) {
		return;
	}

	return do_build_tree(preOrder,0,preOrderLength-1,midOrder,0,midOrderLength-1);
}

BinaryTreeNode* do_build_tree(int* preOrder, int startIndexPreOrder, int endIndexPreOrder, int* midOrder, int startIndexMidOrder, int endIndexMidOrder) {

	BinaryTreeNode* root = new BinaryTreeNode;
	root->left = root->right = NULL;
	root->val = preOrder[startIndexPreOrder];

	int startIndexMid = startIndexMidOrder;
	bool found = false;
	while (startIndexMid <= endIndexMidOrder) {
		if (root->val == midOrder[startIndexMid]){
			found = true;
			break;
		}
		startIndexMid++;
	}

	if (found == false) {
		throw std::exception("not found!\n");
	}

	root->left = do_build_tree(preOrder, startIndexPreOrder + 1, startIndexMid, midOrder, startIndexMidOrder, startIndexMid - 1);
	root->right = do_build_tree(preOrder, startIndexMid + 1, endIndexPreOrder, midOrder, startIndexMid+1, endIndexMidOrder);
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