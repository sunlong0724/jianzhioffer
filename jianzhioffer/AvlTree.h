
#ifndef __AVLTREE_H__
#define __AVLTREE_H__
#include <algorithm>

template <typename T>
struct AvlNode {
	T data;
	int height;
	AvlNode<T> *left;
	AvlNode<T> *right;
	AvlNode(const T theData) :data(theData), height(0), left(NULL), right(NULL) {}
};

template <typename T>
class AvlTree {
public:
	AvlTree<T>():m_root(NULL) {}
	~AvlTree<T>(){}

	void Insert(AvlNode<T> *&root, T x);
	bool Delete(AvlNode<T> *&root, T x);
	bool Contains(AvlNode<T> *root, const T t) const;
	void InorderTraversal(AvlNode<T>*t);
	void PreorderTraversal(AvlNode<T>*t);
	
	AvlNode<T>* FindMin(AvlNode<T> *t) const;
	AvlNode<T>* FindMax(AvlNode<T> *t) const;

private:
	int GetHeight(AvlNode<T> *t);

	/*����ת��������뵼�µĲ�ƽ�⣬������ת��Ҳ������ת��
	*/
	AvlNode<T>* LL(AvlNode<T>* t);

	/*����ת�����Ҳ��뵼�µĲ�ƽ�⡣������ת��Ҳ������ת��
	*/
	AvlNode<T>* RR(AvlNode<T> *t);

	/*˫��ת��t�����ӽڵ�����ӽڵ���뵼�µĲ�ƽ�⡣
	*/
	AvlNode<T>* LR(AvlNode<T> *t);
	AvlNode<T>* RL(AvlNode<T> *t);

public:
	AvlNode<T> *m_root;
};


template <typename T>
AvlNode<T>* AvlTree<T>::FindMin(AvlNode<T> *t) const {
	if (!t) return NULL;
	if (!t->left) return t;
	return FindMin(t->left);
}

template <typename T>
AvlNode<T>* AvlTree<T>::FindMax(AvlNode<T> *t) const {
	if (!t) return NULL;
	if (!t->right) return t;
	return FindMax(t->right);
}

template <typename T>
int AvlTree<T>::GetHeight(AvlNode<T> *t) {
	if (!t) return -1;
	return t->height;
}


/*����ת��������뵼�µĲ�ƽ�⣬������ת��Ҳ������ת��
*/
template <typename T>
AvlNode<T>* AvlTree<T>::LL(AvlNode<T>* t) {
	AvlNode<T>* p = t->left;
	t->left = p->right;
	p->right = t;

	t->height = std::max(GetHeight(t->left), GetHeight(t->right)) + 1;
	p->height = std::max(GetHeight(p->left), GetHeight(p->right)) + 1;

	return p;
}

template <typename T>
AvlNode<T>* AvlTree<T>::RR(AvlNode<T> *t) {
	AvlNode<T>* p = t->right;
	t->right = p->left;
	p->left = t;

	t->height = std::max(GetHeight(t->left), GetHeight(t->right)) + 1;
	p->height = std::max(GetHeight(p->left), GetHeight(p->right)) + 1;

	return p;
}

template <typename T>
AvlNode<T>* AvlTree<T>::LR(AvlNode<T> *t) {
	t->left = RR(t->left);
	return LL(t);
}

template <typename T>
AvlNode<T>* AvlTree<T>::RL(AvlNode<T>* t) {
	t->right = LL(t->right);
	return RR(t);
}

template<typename T>
void AvlTree<T>::Insert(AvlNode<T> *&root, T x) {
	if (root == NULL) {
		root = new AvlNode<T>(x);
		if (!root) {
			fprintf(stdout, "new failed!\n");
			exit(-1);
		}
	}
	else if ( x < root->data) {
		Insert(root->left, x);
		if (GetHeight(root->left) - GetHeight(root->right) == 2) {
			if (x < root->left->data) {//�������������
				root = LL(root);
			}
			else {//���������˫��ת��������������
				root = LR(root);
			}
		}
	}
	else if (x > root->data) {
		Insert(root->right, x);
		if (GetHeight(root->right) - GetHeight(root->left) == 2) {
			if (x > root->right->data) {//�������������
				root = RR(root);
			}
			else {//���������˫��ת��������������
				root = RL(root);
			}
		}
	}
	else {//==

	}
	root->height = std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

template <typename T>
void AvlTree<T>::InorderTraversal(AvlNode<T>* t) {

	if (t) {
		InorderTraversal(t->left);
		fprintf(stdout, "%d,", t->data);
		InorderTraversal(t->right);
	}
}
#endif // !__AVLTREE_H__

