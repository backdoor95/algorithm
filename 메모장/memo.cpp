#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define N 10
typedef struct IncidentEdge
{
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;
typedef struct Vertex
{
	char vName;
	int isVisit;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;
typedef struct
{
	Vertex* vHead;
}GraphType;
void init(GraphType* G)
{
	G->vHead = NULL;
}
void makeVertex(GraphType* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->isVisit = FALSE;
	v->iHead = NULL;
	v->next = NULL;
	Vertex* p = G->vHead;
	if (p == NULL)
		G->vHead = v;
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = v;
	}
}
void makeIncidentEdge(Vertex* v, char aName)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;
	IncidentEdge* q = v->iHead;
	if (q == NULL)
		v->iHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}
Vertex* findVertex(GraphType* G, char vName)
{
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	return p;
}
void insertEdge(GraphType* G, char v1, char v2)
{
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);
	v = findVertex(G, v2);
	makeIncidentEdge(v, v1);
}
typedef struct
{
	Vertex* elem[N];
	int front, rear;
}QueueType;
void initQueue(QueueType* Q)
{
	Q->front = Q->rear = 0;
}
int isQueueEmpty(QueueType* Q)
{
	return Q->rear == Q->front;
}
void enqueue(QueueType* Q, Vertex* v)
{
	Q->rear = (Q->rear + 1) % N;
	Q->elem[Q->rear] = v;
}
Vertex* dequeue(QueueType* Q)
{
	Q->front = (Q->front + 1) % N;
	return Q->elem[Q->front];
}
typedef struct
{
	Vertex* elem[N];
	int top;
}StackType;
void initStack(StackType* S)
{
	S->top = -1;
}
int isStackEmpty(StackType* S)
{
	return S->top == -1;
}
void push(StackType* S, Vertex* v)
{
	S->top++;
	S->elem[S->top] = v;
}
Vertex* pop(StackType* S)
{
	Vertex* v = S->elem[S->top];
	S->top--;
	return v;
}
void dfs(GraphType* G, char vName)// ºñÀç±Í ¹æ½Ä dfs
{
	Vertex* v = findVertex(G, vName);
	IncidentEdge* p;
	StackType S;
	initStack(&S);
	push(&S, v);
	while (!isStackEmpty(&S))
	{
		if (v->isVisit == FALSE)
		{
			v->isVisit = TRUE;
			printf("[%c] ", v->vName);
		}
		for (p = v->iHead; p != NULL; p = p->next)
		{
			v = findVertex(G, p->aName);
			if (v->isVisit == FALSE)
			{
				push(&S, v);
				break;
			}
		}
		if (p == NULL)
			pop(&S);
	}
}
void bfs(GraphType* G, char vName)
{
	Vertex* v = findVertex(G, vName);
	IncidentEdge* p;
	QueueType Q;
	initQueue(&Q);
	v->isVisit = TRUE;
	printf("[%c] ", v->vName);
	enqueue(&Q, v);
	while (!isQueueEmpty(&Q))
	{
		v = dequeue(&Q);
		for (p = v->iHead; p != NULL; p = p->next)
		{
			v = findVertex(G, p->aName);
			if (v->isVisit == FALSE)
			{
				v->isVisit = TRUE;
				printf("[%c] ", v->vName);
				enqueue(&Q, v);
			}
		}
	}
}
void rDfs(GraphType* G, char vName)// Àç±Í ¹æ½Ä dfs
{
	Vertex* v = findVertex(G, vName);
	IncidentEdge* p;
	if (v->isVisit == FALSE)
	{
		v->isVisit = TRUE;
		printf("[%c] ", v->vName);
	}
	for (p = v->iHead; p != NULL; p = p->next)
	{
		v = findVertex(G, p->aName);
		if (v->isVisit == FALSE)
			rDfs(G, v->vName);
	}
}
void print(GraphType* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("[%c] : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next)
			printf("[%c] ", q->aName);
		printf("\n");
	}
}
int main()
{
	GraphType G;
	init(&G);
	makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
	makeVertex(&G, 'd'); makeVertex(&G, 'e');
	insertEdge(&G, 'a', 'b'); insertEdge(&G, 'a', 'c');
	insertEdge(&G, 'a', 'e'); insertEdge(&G, 'b', 'c');
	insertEdge(&G, 'c', 'd'); insertEdge(&G, 'c', 'e');
	insertEdge(&G, 'd', 'e');
	print(&G); getchar();
	dfs(&G, 'd');
	return 0;
}