#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define NoSuchKey 404404
typedef struct TreeNode {
	int key;
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
	if (root == w)
		return root;
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
	R->left = NULL;
	R->right = NULL;
	L->parent = z;
	R->parent = z;
	z->left = L;
	z->right = R;
	return;
}
void insertItem(TreeNode* root, int key)
{
	TreeNode* w = treeSearch(root, key);
	if (isInternal(w))// 내부 노드일때는 그냥 반환
		return;
	else
	{
		w->key = key;
		expandExternal(w);
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
TreeNode* reduceExternal(TreeNode** root, TreeNode* z)// 이 부분에서 많이 고침- 이중포인터 사용
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
int removeElement(TreeNode** root, int key)// 이 부분은 이중 포인터 사용
{
	TreeNode* w = treeSearch(*root, key);
	if (isExternal(w))
		return NoSuchKey;
	int e = w->key;
	TreeNode* z = leftChild(w);
	if (!isExternal(z))
		z = rightChild(w);
	if (isExternal(z))
		reduceExternal(root, z);
	else
	{
		TreeNode* y = inOrderSucc(w);
		z = leftChild(y);
		w->key = y->key;
		reduceExternal(root, z);
	}

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
			insertItem(root, num);
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