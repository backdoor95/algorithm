#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* parent;
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
}TreeNode;
int isExternal(TreeNode* w)
{
	return (w->leftChild == NULL && w->rightChild == NULL);
}
int isInternal(TreeNode* w)
{
	return (w->leftChild != NULL || w->rightChild != NULL);
}
TreeNode* treeSearch(TreeNode)
int main() {

}