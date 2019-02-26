
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

	/*单旋转。左左插入导致的不平衡，向右旋转。也叫右旋转。
	*/
	AvlNode<T>* LL(AvlNode<T>* t);

	/*单旋转。右右插入导致的不平衡。向左旋转。也叫左旋转。
	*/
	AvlNode<T>* RR(AvlNode<T> *t);

	/*双旋转。t的左子节点的右子节点插入导致的不平衡。
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


/*单旋转。左左插入导致的不平衡，向右旋转。也叫右旋转。
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
			if (x < root->left->data) {//左左情况，右旋
				root = LL(root);
			}
			else {//左右情况，双旋转，先左旋后右旋
				root = LR(root);
			}
		}
	}
	else if (x > root->data) {
		Insert(root->right, x);
		if (GetHeight(root->right) - GetHeight(root->left) == 2) {
			if (x > root->right->data) {//右右情况，左旋
				root = RR(root);
			}
			else {//右左情况，双旋转，先右旋后左旋
				root = RL(root);
			}
		}
	}
	else {//==

	}
	root->height = std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

template <typename T>
bool AvlTree<T>::Delete(AvlNode<T>* &t, T x) {
	if (t == NULL) {
		return false;
	}
	else if (t->data == x) {
		if (t->left != NULL &&t->right != NULL) {

			//左子树高度达，左子树中的最大节点的值赋值给本节点，然后删除最大节点
			if (GetHeight(t->left) > GetHeight(t->right)) {
				t->data = FindMax(t->left)->data;
				Delete(t->left, t->data);
			}
			else {//右子树高度大，右子树中的最小节点赋值给本节点，然后删除该最小节点。
				t->data = FindMin(t->right)->data;
				Delete(t->right, t->data);
			}
		}
		else {//左右子树有一个不为空，直接有需要删除的子节点替换即可。
			AvlNode<T>*old = t;
			t = t->left ? t->left : t->right;
			delete old;
		}
	}
	else if (x < t->data) {
		//在左子树树上查找并删除
		Delete(t->left, x);
		//判断是否满足平衡条件
		if (GetHeight(t->right) - GetHeight(t->left) > 1) {
			if (GetHeight(t->right->left) > GetHeight(t->right->right)) {
				//双旋转
				t = RL(t);
			}
			else {
				//RR单旋
				t = RR(t);
			}
		}
		else {//满足平衡性，更新高度值
			t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
		}
	}
	else {//要删除的节点在右子树上
		Delete(t->right, x);
		if (GetHeight(t->left) - GetHeight(t->right) > 1) {
			if (GetHeight(t->left->right) > GetHeight(t->left->left)) {
				//LR双旋
				t = LR(t);
			}
			else {
				//LL单旋
				t = LL(t);
			}
		}
		else {
			t->height = max(GetHeight(t->left), GetHeight(t->right)) + 1;
		}
	}

	return true;
}

template <typename T>
bool AvlTree<T>::Contains(AvlNode<T>* t, const T x) const {
	if (t == NULL) return false;
	if (x < t->data) {
		return Contains(t->left, x);
	}
	else if (x > t->data) {
		return Contains(t->right, x);
	}
	else
		return true;
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

