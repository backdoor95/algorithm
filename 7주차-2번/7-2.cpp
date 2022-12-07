#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define NoSuchKey 404404
typedef struct TreeNode {
	int key, height;
	struct TreeNode* parent;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;
TreeNode* leftChild(TreeNode* v)
{
	return v->left;
}
TreeNode* rightChild(TreeNode* v)
{
	return v->right;
}
void invalidNodeException()
{
	printf("invalidNodeException\n");
	exit(1);
}
bool isRoot(TreeNode* v)
{
	if (v->parent == NULL)
		return true;
	else
		return false;
}
TreeNode* parent(TreeNode* v)
{
	return v->parent;
}
TreeNode* sibling(TreeNode* root, TreeNode* w)
{

	if (leftChild(parent(w)) == w)
		return rightChild(parent(w));
	else
		return leftChild(parent(w));
}
bool isExternal(TreeNode* w)
{
	if (w->left == NULL && w->right == NULL)
		return true;
	else
		return false;
}
bool isInternal(TreeNode* w)
{
	if (w->left != NULL && w->right != NULL)// ||을 &&로 수정함.
		return true;
	else
		return false;
}

TreeNode* treeSearch(TreeNode* v, int key)
{
	if (isExternal(v))
		return v;

	if (key == v->key)
		return v;
	else if (key < v->key)
		return treeSearch(v->left, key);
	else
		return treeSearch(v->right, key);

}
int findElement(TreeNode* root, int key)
{
	TreeNode* w = treeSearch(root, key);
	if (isExternal(w))
		return NoSuchKey;
	else
		return w->key;
}
void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	printf(" %d", root->key);
	preOrder(root->left);
	preOrder(root->right);

}
void expandExternal(TreeNode* z)
{
	TreeNode* L = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* R = (TreeNode*)malloc(sizeof(TreeNode));

	L->left = NULL;
	L->right = NULL;
	L->parent = z;
	L->height = 0;
	R->left = NULL;
	R->right = NULL;
	R->parent = z;
	R->height = 0;

	z->left = L;
	z->right = R;
	z->height = 1;
	return;
}
bool isBalanced(TreeNode* w)
{
	int n = w->left->height - w->right->height;
	if (n < 0)
	{
		n *= -1;
		return n < 2;
	}
	else {
		return n < 2;
	}
}
bool updateHeight(TreeNode* w)
{
	int max = w->left->height > w->right->height ? w->left->height : w->right->height;
	int height = max + 1;
	if (height != w->height)
	{
		w->height = height;
		return true;
	}
	else
		return false;
}
TreeNode* restructure(TreeNode** root, TreeNode* x, TreeNode* y, TreeNode* z)
{
	// 1.
	TreeNode* a, * b, * c;
	TreeNode* t0, * t1, * t2, * t3;
	if (z->key < y->key && y->key < x->key)
	{
		a = z; b = y; c = x;
		t0 = a->left; t1 = b->left; t2 = c->left; t3 = c->right;
	}
	else if (x->key < y->key && y->key < z->key)
	{
		a = x; b = y; c = z;
		t0 = a->left; t1 = a->right; t2 = b->right; t3 = c->right;
	}
	else if (z->key < x->key && x->key < y->key)
	{
		a = z; b = x; c = y;
		t0 = a->left; t1 = b->left; t2 = b->right; t3 = c->right;
	}
	else
	{
		a = y; b = x; c = z;
		t0 = a->left; t1 = b->left; t2 = b->right; t3 = c->right;
	}
	// 2
	if (isRoot(z))
	{
		*root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z)
	{
		z->parent->left = b;
		b->parent = z->parent;
	}
	else if(z->parent->right == z)
	{
		z->parent->right = b;
		b->parent = z->parent;
	}
	// 3
	a->left = t0; a->right = t1;
	// 4
	t0->parent = a; t1->parent = a;
	// 5
	updateHeight(a);
	// 6
	c->left = t2; c->right = t3;
	// 7
	t2->parent = c; t3->parent = c;
	// 8
	updateHeight(c);
	// 9 
	b->left = a; b->right = c;
	// 10
	a->parent = b; c->parent = b;
	// 11
	updateHeight(b);
	return b;
}
void searchAndFixAfterInsertion(TreeNode** root, TreeNode* w)
{
	// Update heights and search for imbalance
	w->height = 1;
	w->left->height = 0;
	w->right->height = 0;
	if (isRoot(w))
		return;
	TreeNode* y, * x;
	TreeNode* z = w->parent;
	while (updateHeight(z) && isBalanced(z))
	{
		if (isRoot(z))
			return;
		z = parent(z);
	}
	if (isBalanced(z))
		return;

	// Fix imbalance
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height)
		x = y->left;
	else
		x = y->right;

	restructure(root,x, y, z);
	return;
}
void insertItem(TreeNode** root, int key)
{
	TreeNode* w = treeSearch(*root, key);
	if (isInternal(w))// 내부 노드일때는 그냥 반환
		return;
	else
	{
		w->key = key;
		expandExternal(w);
		searchAndFixAfterInsertion(root, w);
		return;
	}
}
TreeNode* inOrderSucc(TreeNode* w)
{
	w = rightChild(w);
	if (isExternal(w))
		invalidNodeException();
	while (isInternal(leftChild(w)))
		w = leftChild(w);
	return w;
}

void searchAndFixAfterRemoval(TreeNode**root, TreeNode* z)
{
	TreeNode* x, * y;
	//Update heights and search for imbalance
	while (updateHeight(z) && isBalanced(z))
	{
		if (isRoot(z))
			return;
		z = parent(z);
	}
	if (isBalanced(z))
		return;

	// Fix imbalance
	if (z->left->height > z->right->height)
		y = z->left;
	else
		y = z->right;

	if (y->left->height > y->right->height)
		x = y->left;
	else if (y->left->height < y->right->height)
		x = y->right;
	else
	{
		if (z->left == y)
			x = y->left;
		else if (z->right == y)
			x = y->right;
	}
	TreeNode* b = restructure(root, x, y, z);
	if (isRoot(b))
		return;
	searchAndFixAfterRemoval(root, b->parent);

}


TreeNode* reduceExternal(TreeNode** root, TreeNode* z)// 이 부분에서 많이 고침
{
	TreeNode* w = z->parent;
	TreeNode* zs = sibling(*root, z);

	if (isRoot(w))
	{
		*root = zs;
		zs->parent = NULL;
	}
	else
	{
		TreeNode* g = w->parent;
		zs->parent = g;
		if (w == g->left)
			g->left = zs;
		else
			g->right = zs;
	}
	free(w);
	free(z);
	return zs;
}
int removeElement(TreeNode** root, int key)
{
	TreeNode* w = treeSearch(*root, key);
	TreeNode* zs;
	if (isExternal(w))
		return NoSuchKey;
	int e = w->key;
	TreeNode* z = leftChild(w);
	if (!isExternal(z))
		z = rightChild(w); 
	if (isExternal(z))
		zs = reduceExternal(root, z);// 수정
	else
	{
		TreeNode* y = inOrderSucc(w);
		z = leftChild(y);
		w->key = y->key;
		zs = reduceExternal(root, z);// 수정
	}
	searchAndFixAfterRemoval(root, parent(zs));// 수정
	return e;
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));// root 생성
	root->parent = root->left = root->right = NULL;
	char menu;
	int num, e;
	while (1)
	{
		scanf("%c", &menu);

		switch (menu)
		{
		case 'i':
			scanf("%d", &num);
			getchar();
			insertItem(&root, num);
			break;
		case 'd':
			scanf("%d", &num);
			getchar();
			e = removeElement(&root, num);
			if (e == NoSuchKey)
				printf("X\n");
			else
				printf("%d\n", e);
			break;
		case 's':
			scanf("%d", &num);
			getchar();
			e = findElement(root, num);
			if (e == NoSuchKey)
				printf("X\n");
			else
				printf("%d\n", e);
			break;
		case 'p':
			getchar();
			preOrder(root);
			printf("\n");
			break;
		case 'q':
			getchar();
			return 0;
			break;

		}
	}

	return 0;
}