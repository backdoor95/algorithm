#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 이진탐색트리

typedef struct treeNode {
	int key;
	struct treeNode* lchild;
	struct treeNode* rchild;
	struct treeNode* parent;
}node;

int isExternal(node* w) {
	if (w->lchild == NULL && w->rchild == NULL)
		return 1;
	else
		return 0;
}

int isInternal(node* w) {
	if (w->lchild != NULL || w->rchild != NULL)
		return 1;
	else
		return 0;
}

void getNode(node** w) {
	(*w) = (node*)malloc(sizeof(node));
	(*w)->parent = NULL;
	(*w)->lchild = NULL;
	(*w)->rchild = NULL;
}

void expandExternal(node* w) {//양쪽 외부노드로 확장
	node* newleft;
	node* newright;

	getNode(&newleft);
	getNode(&newright);

	w->lchild = newleft;
	w->rchild = newright;
	newleft->parent = w;
	newright->parent = w;
}

node* treeSearch(node* w, int k) {
	if (isExternal(w))
		return w;

	if (k == w->key)
		return w;
	else if (k < w->key)
		return treeSearch(w->lchild, k);
	else
		return treeSearch(w->rchild, k);
}

void insertKey(node* root, int k) {
	node* w = treeSearch(root, k);

	if (isInternal(w))
		return;
	else {
		w->key = k;
		expandExternal(w);
		return;
	}
}

void findElement(node* root, int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w))
		printf("%d\n", k);
	else
		printf("X\n");
}

node* sibling(node* root, node* z) {// w와 z없애고 붙일 노드 정하기
	if (root == z)
		return root;
	if (z->parent->lchild == z)
		return z->parent->rchild;
	else
		return z->parent->lchild;
}

node* inOrderSucc(node* w) {// 중위순회 계승자 구하기
	node* y = w->rchild;// y는 우선 w의 오른쪽 자식으로 이동 후

	if (isExternal(y))
		return y;
	while (isInternal(y->lchild))// 거기서부터 왼쪽 자식만을 끝까지 따라 내려가면 도달하게 되는 마지막 내부노드임
		y = y->lchild;

	return y;//중위순회 계승자 반환
}

void reduceExternal(node** root, node* z) {
	node* w = z->parent;
	node* zs, * g;
	zs = sibling(*root, z);

	if (w == *root) {
		*root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;

		if (w == g->lchild)
			g->lchild = zs;
		else
			g->rchild = zs;
	}

	free(z);
	free(w);
}
void removeElement(node** root, int k) {
	node* w = treeSearch(*root, k);

	if (isExternal(w)) {
		printf("X\n");
		return;
	}

	//삭제할 노드가 있다면
	node* z = w->lchild;
	if (!isExternal(z))//
		z = w->rchild;
	if (isExternal(z))
		reduceExternal(root, z);
	else {// case2
		node* y = inOrderSucc(w);// 중위순회 계승자 y
		z = y->lchild;//노드 z는 y의 왼쪽 자식인 외부노드
		w->key = y->key;//y의 내용을 w에 복사하고
		reduceExternal(root, z);//노드 y와 z 삭제
	}
	printf("%d\n", k);
}

void printNode(node* root) {
	if (isExternal(root))
		return;
	else {
		printf(" %d", root->key);
		printNode(root->lchild);
		printNode(root->rchild);
	}
}

void freeNode(node* root) {
	if (isExternal(root))
		return;
	else {
		freeNode(root->lchild);
		freeNode(root->rchild);
		free(root);
	}
}

int main() {
	char type;
	int key;

	//node* root = (node*)malloc(sizeof(node));
	node* root;
	getNode(&root);

	while (1) {
		scanf("%c", &type);

		if (type == 'q')
			break;
		else if (type == 'i') {
			scanf("%d", &key);
			getchar();
			insertKey(root, key);
		}
		else if (type == 'd') {
			scanf("%d", &key);
			getchar();
			removeElement(&root, key);//
		}
		else if (type == 's') {
			scanf("%d", &key);
			getchar();
			findElement(root, key);
		}
		else if (type == 'p') {
			printNode(root);
			printf("\n");
		}
	}

	freeNode(root);

	return 0;
}