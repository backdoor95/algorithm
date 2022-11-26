//#include<stdio.h>
//
//int main() {//1번
//	int max_index, i, j;
//	int tmp;
//	int a[] = { 40,10,50,90,20,80,30,60 };
//
//	for (i = 7; i >0; i--)
//	{
//		max_index = i;
//		for (j = 0; j < i; j++)
//		{
//			if (a[max_index] < a[j]) {
//				max_index = j;
//			}
//		}
//		tmp = a[i];
//		a[i] = a[max_index];
//		a[max_index] = tmp;
//
//		for (int i = 0; i < 8; i++)
//		{
//			printf("%d ", a[i]);
//		}
//		printf("\n");
//	}
//}
#include<stdlib.h>
#include<stdio.h>
typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;
TreeNode* makeNode(int data, TreeNode* left, TreeNode* right)
{
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
	p->data = data;
	p->left = left;
	p->right = right;
	return p;
}
struct Que
{
	struct TreeNode* f;
	struct TreeNode* r;
};
void initQueue(Que* q)
{
	q->f = NULL;
	q->r = NULL;
}
int isEmpty(Que* q)
{

}
void InverseTree(TreeNode* root) 
{
	if (root->left == NULL || root->right == NULL)
		return;
	TreeNode* p = root->left;
	root->left = root->right;
	root->right = p;
	InverseTree(root->left);
	InverseTree(root->right);

}
void Print(TreeNode* root)
{
	printf("%d ", root->data);
	printf("%d ", root->left->data);
	printf("%d ", root->right->data);
	printf("%d ", root->left->left->data);
	printf("%d ", root->left->right->data);
	printf("%d ", root->right->left->data);
	printf("%d ", root->right->right->data);
}
int main() {
	TreeNode* n1 = makeNode(2, NULL, NULL);
	TreeNode* n2 = makeNode(4, NULL, NULL);
	TreeNode* n3 = makeNode(6, NULL, NULL);
	TreeNode* n4 = makeNode(9, NULL, NULL);
	TreeNode* n5 = makeNode(3, n1, n2);
	TreeNode* n6 = makeNode(8, n3, n4);
	TreeNode* root = makeNode(5, n5, n6);

	printf("Before : ");
	Print(root);
	// 재귀함수를 사용하여 트리를 반전시키는 코드를 구현해보겠습니다.
	printf("\n");
	InverseTree(root);
	printf("After : ");
	Print(root);

}