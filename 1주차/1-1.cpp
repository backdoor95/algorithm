#include<stdio.h>
#include<stdlib.h>

typedef struct DListNode
{
	char elem;
	struct DListNode* prev;
	struct DListNode* next;

}DListNode;

typedef struct
{
	DListNode* H;//header
	DListNode* T;// tail
}DListType;
// (*DL).H ---> ok 또는 DL->H
// *DL.H---_> no

void init(DListType* DL)// 모조건 포인터로 받겠다.
{
	DL->H = DL->T = NULL;
}

void insertFirst(DListType* DL, char c)
{
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));// 새로운 삽입되어진는놈, 메모리를 만듬
	DListNode* p = DL->H;
	node->elem = c;
	node->prev = node->next = NULL;

	if (p == NULL)// 연결리스트가 비어있으면, 그림으로 그려봐서 화살표를 그려보자, 화살표는 대체로 2개, 많아야3,4개
	{
		DL->H = DL->T = node;
	}
	else
	{
		node->next = p;
		p->prev = node;
		DL->H = node;
	}
}
void insertLast(DListType* DL, char c)
{
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));// 새로운 삽입되어진는놈, 메모리를 만듬
	DListNode* p = DL->H;
	node->elem = c;
	node->prev = node->next = NULL;

	if (p == NULL)// 연결리스트가 비어있으면, 그림으로 그려봐서 화살표를 그려보자, 화살표는 대체로 2개, 많아야3,4개
	{
		DL->H = DL->T = node;
	}
	else
	{
		node->prev = p;
		p->next = node;
		DL->T = node;
	}
}
void insert(DListType* DL, int pos, char c)
{
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));// 새로운 삽입되어진는놈, 메모리를 만듬
	DListNode* p = DL->H;

	if (pos == 1)
		insertFirst(DL, c);
	else
	{
		for (int i = 1; i < pos - 1; i++) {
			p = p->next;
		}
		node->elem = c;
		node->prev = p;
		node->next = p->next;
		if (p->next == NULL)// insertLast 일때인듯?
		{
			p->next = node;
			DL->T = node;
		}
		else
		{
			p->next->prev = node;// 순서 조심
			p->next = node;
		}
	}
}
char deleteFirst(DListType* DL)
{
	DListNode* p = DL->H;
	char c = p->elem;// ==(*p).elem
	if (p->next == NULL)
		DL->H = DL->T = NULL;
	else
	{
		p->next->prev = NULL;
		DL->H = p->next;
	}
	free(p);
	return c;
}
char deleteLast(DListType* DL)
{
	DListNode* p = DL->T;
	char c = p->elem;
	if (p->prev == NULL)
		DL->H = DL->T = NULL;
	else
	{
		p->prev->next = NULL;
		DL->T = p->prev;
	}
	free(p);

	return c;
}
char Delete(DListType* DL, int pos)
{
	DListNode* p = DL->H;
	char c;

	if (pos == 1)
		c = deleteFirst(DL);
	else
	{
		for (int i = 1; i < pos; i++) {
			p = p->next;
		}

		if (p->next == NULL)
			c = deleteLast(DL);
		else
		{
			c = p->elem;
			p->prev->next = p->next;
			p->next->prev = p->prev;
			free(p);
		}
	}
	return c;
}
void print(DListType* DL)
{
	for (DListNode* p = DL->H; p != NULL; p = p->next)
		printf("[%c] <=> ", p->elem);
	printf("\b\b\b\b   \n");// \b: backspace 라는 뜻
}
int main() {
	DListType DL;
	init(&DL);

	insertFirst(&DL, 'A'); insertFirst(&DL, 'B');
	print(&DL); getchar();// getchar() : 텀을 주기위해 넣어준것임

	insert(&DL, 1, 'C');// 첫번째 노드
	insert(&DL, 3, 'D');
	print(&DL); getchar();

	insertLast(&DL, 'E');
	print(&DL); getchar();

	//printf("[%c] is deleted\n", deleteFirst(&DL));
	//print(&DL); getchar();


	return 0;
}