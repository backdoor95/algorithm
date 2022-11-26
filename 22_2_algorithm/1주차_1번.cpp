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
// (*DL).H ---> ok �Ǵ� DL->H
// *DL.H---_> no

void init(DListType* DL)// ������ �����ͷ� �ްڴ�.
{
	DL->H = DL->T = NULL;
}

void insertFirst(DListType* DL, char c)
{
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));// ���ο� ���ԵǾ����³�, �޸𸮸� ����
	DListNode* p = DL->H;
	node->elem = c;
	node->prev = node->next = NULL;

	if (p == NULL)// ���Ḯ��Ʈ�� ���������, �׸����� �׷����� ȭ��ǥ�� �׷�����, ȭ��ǥ�� ��ü�� 2��, ���ƾ�3,4��
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
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));// ���ο� ���ԵǾ����³�, �޸𸮸� ����
	DListNode* p = DL->H;
	node->elem = c;
	node->prev = node->next = NULL;

	if (p == NULL)// ���Ḯ��Ʈ�� ���������, �׸����� �׷����� ȭ��ǥ�� �׷�����, ȭ��ǥ�� ��ü�� 2��, ���ƾ�3,4��
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
	DListNode* node = (DListNode*)malloc(sizeof(DListNode));// ���ο� ���ԵǾ����³�, �޸𸮸� ����
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
		if (p->next == NULL)
		{
			p->next = node;
			DL->T = node;
		}
		else
		{
			p->next->prev = node;// ���� ����
			p->next = node;
		}
	}
}
char deleteFirst(DListType* DL)
{
	DListNode* p = DL->H;
	char c = p->elem;
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
char delete(DListType* DL, int pos)
{
	DListNode* p = DL->H;
	char c;

	if (pos == 1)
		c = deleteFirst(DL);
	else
	{
		for (int i = 1; i < pos ; i++) {
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
	printf("\b\b\b\b   \n");// \b: backspace ��� ��
}
int main() {
	DListType DL;
	init(&DL);

	insertFirst(&DL, 'A'); insertFirst(&DL, 'B');
	print(&DL); getchar();// getchar() : ���� �ֱ����� �־��ذ���
	
	insert(&DL, 1, 'C');// ù��° ���
	insert(&DL, 3, 'D');
	print(&DL); getchar();

	insertLast(&DL, 'E');
	print(&DL); getchar();

	//printf("[%c] is deleted\n", deleteFirst(&DL));
	//print(&DL); getchar();

	
	return 0;
}