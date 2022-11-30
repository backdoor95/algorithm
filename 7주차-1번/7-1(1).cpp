#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode {
	int key;
	struct TreeNode* parent;
	struct TreeNode* left;// left child
	struct TreeNode* right;// right child

}TreeNode;
int isExternal(TreeNode* w)
{
	return (w->left == NULL && w->right == NULL);
}
int isInternal(TreeNode* w)
{
	return (w->left != NULL || w->right != NULL);
}
TreeNode* treeSearch(TreeNode* v, int k)
{
	if (isExternal(v))// 외부 노드일때
		return v;

	if (k == v->key)
		return v;
	else if (k < v->key)
		return treeSearch(v->left, k);
	else// k>v->key 일때
		return treeSearch(v->right, k);
}
void expandExternal(TreeNode* w)
{
	TreeNode* l = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* r = (TreeNode*)malloc(sizeof(TreeNode));
	l->left = l->right = NULL;
	l->parent = w;
	r->left = r->right = NULL;
	r->parent = w;
	w->left = l;
	w->right = r;
}
void insertItem(TreeNode* root, int k)
{	// 이번 문제에서는 중복키를 허용하지 않는다고함.
	TreeNode* w = treeSearch(root, k);
	//if (!isExternal(w))// 외부노드가 아닐때 = 내부 노드일때.  중복키 방지 코드
	//	return;
	//else
	//{
	//	w->key = k;
	//	expandExternal(w);
	//}
	w->key = k;
	expandExternal(w);
}
TreeNode* sibling(TreeNode* z)
{
	if (z->parent->left == z)
		return z->parent->right;
	else
		return z->parent->left;
}
TreeNode* reduceExternal(TreeNode* root, TreeNode* z)
{
	TreeNode* w = z->parent;
	TreeNode* g = w->parent;
	TreeNode* zs = sibling(z);

	zs->parent = g;
	if (g == NULL)
		root = zs;
	else
		if (w == g->left)
			g->left = zs;
		else
			g->right = zs;
	free(w);
	free(z);
	return zs;
}
TreeNode* inOrderSucc(TreeNode* w)
{
	w = w->right;
	if (isExternal(w))
		printf("외부 노드입니다.\n");
	while (w->left != NULL)
		w = w->left;
	return w;
}
int removeElement(TreeNode* root, int k)
{
	TreeNode* w, * z, * y;
	w = treeSearch(root, k);

	if (isExternal(w))
		return -9999;
	int e = w->key;// 수정
	z = w->left;
	if (!isExternal(z))
		z = w->right;
	if (isExternal(z))// case 1
		reduceExternal(root, z);
	else// case 2
	{
		z = inOrderSucc(w);
		y = z->parent;
		w->key = y->key;
		reduceExternal(root, z);
	}
	return e;
}
void preOrder(TreeNode* root)
{
	if (isExternal(root))
		return;
	printf(" %d",root->key);
	preOrder(root->left);
	preOrder(root->right);

}
int findElement(TreeNode*root, int k)
{
	TreeNode* w = treeSearch(root, k);
	if (isExternal(w))
		return -1;
	else
		return w->key;
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
		    e = removeElement(root, num);
			if (e == -1)
				printf("X\n");
			else
				printf("%d\n", e);
			break;
		case 's':
			scanf("%d", &num);
			getchar();
			if (findElement(root, num) == -1)
				printf("X\n");
			else
				printf("%d\n", findElement(root, num));
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