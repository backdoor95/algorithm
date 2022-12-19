#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define Fresh 0
#define Visited 1
#define Tree 2
#define Cross 3
#define N 100
int n;
typedef struct Edge
{
	int v1, v2;
	int eLable;
	struct Edge* next;
}Edge;
typedef struct Vertex
{
	int vLable;
	int VertexNodeNumber;
	struct Vertex* next;
}Vertex;
typedef struct Graph
{
	Vertex* vHead;
	Edge* eHead;
	Edge* AdjMatrix[N][N];
}Graph;
void initGraph(Graph* G)
{
	G->eHead = NULL;
	G->vHead = NULL;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			G->AdjMatrix[i][j] = NULL;
	}
	return;
}
Vertex* insertVertex(Graph* G, int VertexNumber)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->VertexNodeNumber = VertexNumber;
	v->vLable = Fresh;
	v->next = NULL;
	Vertex* q = G->vHead;
	if (q == NULL)
	{
		G->vHead = v;
	}
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = v;
	}
	return v;
}
void insertEdge(Graph* G, Vertex* v1, Vertex* v2)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->v1 = v1->VertexNodeNumber;
	e->v2 = v2->VertexNodeNumber;
	e->eLable = Fresh;
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
	int i = v1->VertexNodeNumber - 1;
	int j = v2->VertexNodeNumber - 1;
	G->AdjMatrix[i][j] = e;
	G->AdjMatrix[j][i] = e;
}
Vertex* findVertex(Graph* G, int nodeNumber)
{
	Vertex* p = G->vHead;
	while (p->VertexNodeNumber != nodeNumber)
	{
		p = p->next;
		if (p == NULL)
			break;
	}
	return p;
}
Vertex* opposite(Graph* G, Vertex* v, Edge* e)
{
	if (e->v1 == v->VertexNodeNumber)
	{
		return findVertex(G, e->v2);
	}
	else if (e->v2 == v->VertexNodeNumber)
	{
		return findVertex(G, e->v1);
	}
}
typedef struct queNode {
	Vertex* v;
	struct queNode* next;
}queNode;
typedef struct Que {
	queNode* f;
	queNode* r;
}Que;
void initQue(Que* q)
{
	q->f = NULL;
	q->r = NULL;
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
void enqueue(Que* Q, Vertex* v)// addLast(v)
{
	queNode* p = getQueNode();
	p->v = v;
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
queNode* dequeue(Que* Q)
{
	if (isEmpty(Q))
	{
		printf("Que is empty\n");
	}
	queNode* p = Q->f;
	Q->f = Q->f->next;
	if (Q->f == NULL)
		Q->r = NULL;
	return p;
}
void BFS(Graph* G, Que* Q, int start)
{
	Vertex* s = findVertex(G, start);// s는 start의 약자이다.
	enqueue(Q, s);

	while (!isEmpty(Q))
	{
		queNode* p = dequeue(Q);
		p->v->vLable = Visited;
		Vertex* v = p->v;
		printf("%d\n", v->VertexNodeNumber);
		for (int i = 0; i < n; i++)
		{
			if (G->AdjMatrix[v->VertexNodeNumber - 1][i] != NULL)
			{
				Edge* e = G->AdjMatrix[v->VertexNodeNumber - 1][i];
				if (e->eLable == Fresh)
				{
					Vertex* w = opposite(G, v, e);
					if (w->vLable == Fresh)
					{
						e->eLable = Tree;
						w->vLable = Visited;
						//printf("%d\n", v->VertexNodeNumber);
						enqueue(Q, w);
					}
					else
					{
						e->eLable = Cross;
					}
				}
			}

		}
		freeQueNode(p);
	}
}
int main() {
	int m, s;// s는 시작 정점
	int v1, v2;
	Graph G;
	Que Q;
	Vertex* Vertex_1, * Vertex_2;
	initGraph(&G);
	initQue(&Q);

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 1; i <= n; i++)
	{// 정점 생성
		insertVertex(&G, i);
	}

	for (int i = 0; i < m; i++)// 간선 생성
	{
		scanf("%d %d", &v1, &v2);
		Vertex_1 = findVertex(&G, v1);
		Vertex_2 = findVertex(&G, v2);
		insertEdge(&G, Vertex_1, Vertex_2);
	}

	BFS(&G, &Q, s);


	return 0;
}