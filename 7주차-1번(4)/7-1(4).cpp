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
TreeNode* leftChild(TreeNode*v)
{
	return v->left;
}
TreeNode* rightChild(TreeNode*v)
{
	return v->right;	
}
void invaildNodeException()
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

}