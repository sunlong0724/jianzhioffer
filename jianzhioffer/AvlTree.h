#pragma once

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
	AvlTree<T>() {}
	~AvlTree<T>(){}

	void Insert(AvlNode<T> *&t, T x);
	bool Delete(AvlNode<T> *&t, T x);
	bool Contains(AvlNode<T> *t, const T t) const;
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
	AvlNode<T> *root;
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
	AvlNode<T>* p = RR(t->left);
}