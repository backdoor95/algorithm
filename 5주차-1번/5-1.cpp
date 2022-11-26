#include<stdio.h>
#include<stdlib.h>
// 합병정렬은 stable 정렬이다.
typedef struct Node// 단일연결리스트
{
	int data;
	struct Node* next;
}Node;
typedef struct List
{
	Node* Head;

}List;
void Init(List* L)
{
	L->Head = NULL;
}
Node* newNode(int data)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->data = data;
	p->next = NULL;
	return p;
}
void AddNode(List* list, int size)
{
	int k;

	Node* p;
	for (int i = 1; i <= size; i++)
	{
		scanf("%d", &k);
		if (i == 1)
		{
			list->Head = newNode(k);
			p = list->Head;
		}
		else
		{
			p->next = newNode(k);// 내 실수 부분 1. 먼저 만들고 그다음에 이어줘야한다.
			p = p->next;
		}
	}
}
void Print(List* list)
{
	Node* p = list->Head;

	while (p != NULL)
	{
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}

void merge(List* L, List* L1, List* L2)
{
	Node* a = L1->Head;
	Node* b = L2->Head;
	Node* p;

	if (a->data <= b->data)
	{
		L->Head = a;
		a = a->next;
		p = L->Head;
	}
	else
	{
		L->Head = b;
		b = b->next;
		p = L->Head;
	}
	while ((a != NULL) && (b != NULL))
	{
		if (a->data <= b->data)
		{
			p->next = a;
			a = a->next;
			p = p->next;
		}
		else
		{
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	while (a != NULL)
	{
		p->next = a;
		p = p->next;
		a = a->next;
	}
	while (b != NULL)
	{
		p->next = b;
		p = p->next;
		b = b->next;
	}

}
void partition(List* L, List* L1, List* L2, int n)
{
	Node* p = L->Head;
	L1->Head = p;
	for (int i = 1; i < (n / 2); i++)
		p = p->next;
	L2->Head = p->next;
	p->next = NULL;
}
void mergeSort(List* L, int n)
{
	List L1, L2;

	if (n <= 1)
		return;

	partition(L, &L1, &L2, n);
	printf("L1 = ");
	Print(&L1);
	printf("L2 = ");
	Print(&L2);

	if (n % 2 == 0)
	{
		mergeSort(&L1, n / 2);
		mergeSort(&L2, n / 2);
	}
	else
	{
		mergeSort(&L1, n / 2);
		mergeSort(&L2, n / 2 + 1);
	}
	merge(L, &L1, &L2);

}

int main() {
	List list;
	int n, data;

	scanf("%d", &n);
	Init(&list);

	AddNode(&list, n);

	mergeSort(&list, n);

	Print(&list);
}