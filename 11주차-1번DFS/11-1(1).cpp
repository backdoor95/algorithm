#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define Fresh 0
#define Visited 1
#define Tree 2
#define Back 3
int n;// 정점의 개수

typedef struct Edge
{
	int v1, v2;
	int eLable;
	struct Edge* next;
}Edge;
typedef struct IncidentEdge
{
	int adjacentVertexNumber;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;
typedef struct Vertex
{
	int vLable;
	int VertexNodeNumber;
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
void insertIncidentEdge(Vertex* v, Edge* e, int VertexNumber)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->adjacentVertexNumber = VertexNumber;
	p->e = e;
	p->next = NULL;
	IncidentEdge* q = v->iHead;
	IncidentEdge* r = v->iHead;
	if (q == NULL)
	{
		v->iHead = p;
	}
	else
	{
		while (q!= NULL)
		{
			if (q->adjacentVertexNumber > VertexNumber)
			{
				if (q == v->iHead)
				{
					v->iHead = p;
					p->next = q;
				}
				else
				{
					r->next = p;
					p->next = q;
				}
				return;
			}
			r = q;
			q = q->next;
		}
		r->next = p;// 끝까지 올때
	}
 }
Vertex* insertVertex(Graph* G, int VertexNumber)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->VertexNodeNumber = VertexNumber;
	v->vLable = Fresh;
	v->iHead = NULL;
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
	if (v1->VertexNodeNumber == v2->VertexNodeNumber)
	{
		insertIncidentEdge(v1, e, v1->VertexNodeNumber);
	}
	else 
	{
		insertIncidentEdge(v1, e, v2->VertexNodeNumber);
		insertIncidentEdge(v2, e, v1->VertexNodeNumber);
	}
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
Vertex* opposite(Graph *G, Vertex* v, Edge* e)
{
	if (e->v1 == v->VertexNodeNumber)
	{
		return findVertex(G, e->v2);
	}
	else if(e->v2==v->VertexNodeNumber)
	{
		return findVertex(G, e->v1);
	}
}
void rDFS(Graph* G, Vertex* v)
{
	v->vLable = Visited;
	printf("%d\n", v->VertexNodeNumber);
	IncidentEdge* p = v->iHead;
	Vertex* w;
	Edge* e;
	while (p != NULL)
	{
		e = p->e;
		if (e->eLable == Fresh)
		{
			w = opposite(G, v, p->e);


			if (w->vLable == Fresh)
			{
				e->eLable = Tree;
				rDFS(G, w);
			}
			else
			{
				e->eLable = Back;
			}
		}
		p = p->next;
	}
}
void DFS(Graph* G, int start)
{
	Vertex* p = findVertex(G, start);

	rDFS(G, p);
}
int main() {
	int m, s;// s는 시작 정점
	int v1, v2;
	Graph G;
	Vertex* Vertex_1, * Vertex_2;
	initGraph(&G);

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

	DFS(&G, s);


	return 0;
}