#include<stdio.h>
#include<stdlib.h>
//미완성
typedef struct Vertex
{
	int name;
	struct Vertex* next;
}Vertex;
typedef struct Edge
{
	Vertex* v1, * v2;
	int weight;
	struct Edge* next;
}Edge;
typedef struct Graph
{
	Vertex* vHead;
	Edge* eHead;
}Graph;
typedef struct Sack
{
	Vertex* vHead;
	Edge* eHead;
}Sack;
void initSack(Sack* S)
{
	S->eHead = NULL;
	S->vHead = NULL;
}
void initGraph(Graph* G)
{
	G->eHead = NULL;
	G->vHead = NULL;
}
Vertex* findVertex(Graph* G, int name)
{
	Vertex* p = G->vHead;
	while (p->next != NULL)
	{
		if (p->name == name)
			return p;
		p = p->next;
	}
	return p;
}
void insertVertex(Graph* G, int v)
{
	Vertex* p = (Vertex*)malloc(sizeof(Vertex));
	p->name = v;
	p->next = NULL;
	Vertex* q = G->vHead;
	if (q == NULL)
	{
		G->vHead = p;
	}
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
	}
}
void insertEdge(Graph* G, int v1, int v2, int weight)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = findVertex(G, v1);
	e->v2 = findVertex(G, v2);
	e->weight = weight;
	e->next = NULL;
	Edge* q = G->eHead;
	if (q == NULL)
	{
		G->eHead = e;
	}
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = e;
	}
}
//Que 
typedef struct queNode
{
	Edge* e;
	struct queNode* next;

}queNode;
typedef struct Que
{
	queNode* r;
	queNode* f;
}Que;
void initQue(Que* q)
{
	q->r = NULL;
	q->f = NULL;
}
int isEmpty(Que* q)
{
	return (q->f == NULL);
}
queNode* getQueNode()
{
	queNode* q = (queNode*)malloc(sizeof(queNode));
	q->next = NULL;
	return q;
}
void freeQueNode(queNode* q)
{
	free(q);
	q = NULL;
}
void enqueue(Que* Q, Edge* e)
{
	queNode* p = getQueNode();
	p->e = e;
	if (isEmpty(Q))
	{
		Q->f = p;
		Q->r = p;
	}
	else
	{
		Q->r->next = p;
		Q->r = p;
	}
}
Edge* removeMin(Que* Q)
{
	queNode* p = Q->f;
	queNode* r = p;// r은 que에서 제일 작은 weight를 가진값이다.
	Edge* e = p->e;

	int minWeight = p->e->weight;

	while (p != NULL)
	{
		if (p->e->weight < minWeight)
		{
			minWeight = p->e->weight;
			r = p;
			e = p->e;
		}
		p = p->next;
	}

	p = Q->f;
	queNode* back = Q->f;
	while (p != NULL)
	{
		if (p == r)
		{
			if (p == Q->f)
			{
				Q->f = p->next;
				free(r);
				r = NULL;
				break;
			}
			else if (p == Q->r)
			{
				back->next = NULL;
				Q->r = back;
				free(r);
				r = NULL;
				break;
			}
			else
			{
				back->next = r->next;
				free(r);
				r = NULL;
				break;
			}
		}
		back = p;
		p = p->next;
	}

	return e;
}
void insertQue(Graph* G, Que* Q)
{
	// 모든 간선들을 큐에 넣어준다.
	Edge* p = G->eHead;
	while (p != NULL)
	{
		enqueue(Q, p);
		p = p->next;
	}
}
int getParent(int parent[], int x) 
{
	if (parent[x] == x)return x;
	return getParent(parent, parent[x]);
}
void unionParent(int parent[], int a, int b)
{
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a < b)parent[b] = a;
	else parent[a] = b;
}
int findParent(int parent[], int a, int b)
{
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b) return 1;
	return 0;
}

void KruskalMST(Graph* G, int n)
{
	Que Q;
	int cnt = 0;
	initQue(&Q);
	insertQue(G, &Q);

	int* parent = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i <= n; i++)
		parent[i] = i;
	// 싸이클이 형성시키면 그래프에 포함시키면 안된다.

	
	while (!isEmpty(&Q))
	{
		Edge* e = removeMin(&Q);

		if (!findParent(parent, e->v1->name, e->v2->name))
		{
			unionParent(parent, e->v1->name, e->v2->name);
			printf(" %d", e->weight);
			cnt += e->weight;

		}
		
	}

	printf("\n%d\n", cnt);

}
int main() {

	Graph G;
	initGraph(&G);
	int n, m;
	int weight, v1, v2;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
	{
		insertVertex(&G, i);
	}

	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &weight);
		insertEdge(&G, v1, v2, weight);
	}
	// Sack : 물건을 넣어 어깨에 메고 다닐 수 있게 만든 자루.
	KruskalMST(&G, n);

	return 0;
}