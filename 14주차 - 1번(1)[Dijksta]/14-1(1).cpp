#include<stdio.h>
#include<stdlib.h>
#define INFINITY 1000000
typedef struct Edge
{
	int v1, v2;
	int weight;
	struct Edge* next;
}Edge;
typedef struct InCidentEdge
{
	Edge* e;
	struct InCidentEdge* next;
}IncidentEdge;
typedef struct Vertex
{
	int name;
	int distance;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;
typedef struct Graph
{
	Vertex* vHead;
	Edge* eHead;
}Graph;
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
	return p;// 추가
}
void insertVertex(Graph* G, int v)
{
	Vertex* p = (Vertex*)malloc(sizeof(Vertex));
	p->distance = INFINITY;
	p->name = v;
	p->next = NULL;
	p->iHead = NULL;
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
void insertIncidentEdge(Graph* G, int vName, Edge* e)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->e = e;
	p->next = NULL;
	Vertex* V = findVertex(G, vName);
	IncidentEdge* q = V->iHead;
	if (q == NULL)
	{
		V->iHead = p;
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
	e->v1 = v1;
	e->v2 = v2;
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
	insertIncidentEdge(G, v1, e);
	insertIncidentEdge(G, v2, e);

}
Vertex* opposite(Graph* G, Vertex* v, Edge* e)
{
	Vertex* p1 = findVertex(G, e->v1);
	Vertex* p2 = findVertex(G, e->v2);

	if (v->name == e->v1)
		return p2;
	else
		return p1;
}
//Que 코드
typedef struct queNode
{
	Vertex* v;
	struct queNode* next;
}queNode;
typedef struct Que
{
	queNode* f;
	queNode* r;
}Que;
void initQue(Que* q)// 이중연결리스트로 queue를 만듬
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
void enqueue(Que* Q, Vertex* v)
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
Vertex* removeMin(Que* Q)
{
	queNode* p = Q->f;
	queNode* r = p;
	Vertex* k = p->v;
	int minNum = p->v->distance;
	while (p != NULL)
	{
		if (p->v->distance < minNum)
		{
			minNum = p->v->distance;
			r = p;
			k = p->v;
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
	return k;
}
void insertQue(Graph* G, Que* Q)
{// 모든 정점을  큐에 넣어준다.
	Vertex* p = G->vHead;
	while (p != NULL)
	{
		enqueue(Q, p);
		p = p->next;
	}
}
int elementOfQue(Que* Q, Vertex* z)
{
	queNode* p = Q->f;
	while (p != NULL)
	{
		if (z->name == p->v->name)
			return 1;
		p = p->next;
	}
	return 0;
}
void DijkstraShortestPaths(Graph* G, int s , int n)
{
	Que Q;
	Que storageQue;// 출력할때 사용할 que

	initQue(&Q);
	initQue(&storageQue);

	Vertex* start = findVertex(G, s);
	Vertex* MinVertex = NULL;
	start->distance = 0;
	insertQue(G, &Q);// Q에 모든 정점을 넣는다.

	while (!isEmpty(&Q))
	{
		Vertex* u = removeMin(&Q);

		IncidentEdge* p = u->iHead;
		while (p != NULL)
		{
			Vertex* z = opposite(G, u, p->e);
			
			if (elementOfQue(&Q, z))
			{
				if (u->distance + p->e->weight < z->distance) {
					z->distance = u->distance + p->e->weight;
				}
			}
			p = p->next;
		}
	}

	Vertex* p = G->vHead;
	while (p != NULL)
	{
		if(p->distance!=0&&p->distance!=INFINITY)
			printf("%d %d\n", p->name, p->distance);
		p = p->next;
	}

}
int main() {

	Graph G;
	initGraph(&G);
	int n, m, start;// n = 정점의 개수, m= 간선의 개수, start = 시작정점
	int weight, v1, v2;
	scanf("%d %d %d", &n, &m, &start);

	for (int i = 1; i <= n; i++)
	{
		insertVertex(&G, i);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &weight);
		insertEdge(&G, v1, v2, weight);
	}

	DijkstraShortestPaths(&G, start, n);
	
	return 0;
}