
/*

bst �������ʱ(��������������������������
 (1)�����ǿ���
 (2)���Ǿ������¶��������ʡ������������գ������������нڵ��ֵ�������ĸ��ڵ�ֵС�������������գ������������нڵ��ֵ�������ĸ��ڵ�ֵ�����������ֱ�Ϊ�����������
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
������������ң�
1.�����Ϊ�գ�����Ҳ�����pre��ֵ��node������false��
2.������ҵ�����ֵ��node������true��
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
�����������ӣ�
1.�����ö����������û��Ҫ��ӵ�Ԫ�أ����֮������true������У�����false��
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
���������ɾ��Ԫ��
1.Ҫɾ����Ԫ��ΪҶ�ӽڵ㣬ֱ��ɾ��
2.Ҫɾ����Ԫ��������������������ֱ��ɾ���������������ڵ���������ڵ��滻
3.Ҫɾ����Ԫ��ͬʱ������������ֱ��ɾ�����ҵ��ýڵ����������ڵ㣬�滻ɾ���ڵ�
*/

template <typename T>
bool SearchBSTDelete(BinaryTreeNode<T>* &root, T key) {
	if (!root) {
		return false;
	}
	else {
		if (key == root->data) {
			if (root->right == NULL) {//ֻ��������
				BinaryTreeNode<T>* p = root;
				root = root->left;
				delete p;
			}
			else if (root->left == NULL) {//ֻ��������
				BinaryTreeNode<T>* p = root;
				root = root->right;
				delete p;
			}
			else {//ͬʱ����������
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