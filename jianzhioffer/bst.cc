
/*

bst 二叉查找时(二叉搜索树、二叉排序树）。
 (1)它或是空树
 (2)或是具有以下二叉树性质。若左子树不空，左子树上所有节点的值都比它的根节点值小。若右子树不空，右子树上所有节点的值都比它的根节点值大。左右子树分别都为二叉查找树。
*/

template <typename T>
struct BinaryTreeNode {
	T data;
	int height;
	BinaryTreeNode<T> *left;
	BinaryTreeNode<T> *right;
	BinaryTreeNode(const T theData) :data(theData), height(0), left(NULL), right(NULL) {}
};


/*
二叉查找树查找：
1.如果树为空，或查找不到，pre赋值到node，返回false。
2.如果查找到，赋值到node，返回true。
*/
template <typename T>
bool SearchBST(BinaryTreeNode<T>* root, T key, BinaryTreeNode<T>* &pre, BinaryTreeNode<T>* &node) {
	if (!root){
		node = pre;
		return false;
	}
	else {
		if (key == root->data) {
			node = root;
			return true;
		}
		else if (key > root->data) {
			return SearchBST(root->right, key, root, node);
		}
		else {
			return SearchBST(root->left, key, root, node);
		}
	}
}

/*
二叉查找树添加：
1.遍历该二叉树，如果没有要添加的元素，添加之，返回true。如果有，返回false。
*/

template <typename T>
bool SearchBSTInsert(BinaryTreeNode<T>* &root, T key) {
	BinaryTreeNode<T>* node = NULL;
	if (!SearchBST(root, key, NULL, node)) {
		BinaryTreeNode<T>* p = new BinaryTreeNode<T>(key);

		if (!node) {
			root = p;
		}
		else if (key > node->data) {
			node->right = p;
		}
		else {
			node->left = p;
		}
		return true;
	}
	else {
		return false;
	}
}

/*
二叉查找树删除元素
1.要删除的元素为叶子节点，直接删除
2.要删除的元素有左子树或右子树，直接删除，并用左子树节点或右子树节点替换
3.要删除的元素同时有左右子树，直接删除，找到该节点的中序后续节点，替换删除节点
*/

template <typename T>
bool SearchBSTDelete(BinaryTreeNode<T>* &root, T key) {
	if (!root) {
		return false;
	}
	else {
		if (key == root->data) {
			if (root->right == NULL) {//只有左子树
				BinaryTreeNode<T>* p = root;
				root = root->left;
				delete p;
			}
			else if (root->left == NULL) {//只有右子树
				BinaryTreeNode<T>* p = root;
				root = root->right;
				delete p;
			}
			else {//同时有左右子树
				BinaryTreeNode<T>* p = root->right;
				BinaryTreeNode<T>* s = p;
				while (p->left) {
					s = p;
					p = p->left;
				}
				root->data = p->data;
				if (s == p) {
					root->right = NULL;
				}
				else {
					s->left = NULL;
				}
				delete p;
			}
			return true;
		}
		else if (key > root->data) {
			return SearchBSTDelete(root->right, key);
		}
		else {
			return SearchBSTDelete(root->left, key);
		}
	}
}