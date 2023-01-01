#include<stdio.h>
#include<stdlib.h>
#define INFINITY 1000000
typedef struct Edge
{
	int originVertex;
	int destinationVertex;
	int weight;
	struct Edge* next;
}Edge;
typedef struct Vertex
{
	int name;
	int distance;
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
	while (p != NULL)
	{
		if (p->name == name)
			return p;
		p = p->next;
	}
	
}
void insertVertex(Graph* G, int v)
{
	Vertex* p = (Vertex*)malloc(sizeof(Vertex));
	p->distance = INFINITY;
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
void insertEdge(Graph* G, int ori, int dest, int weight)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->originVertex = ori;
	e->destinationVertex = dest;
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
int minDistance(int x, int y)
{
	if (x <= y)
		return x;
	else
		return y;
}
void BellmanFordShortestPaths(Graph* G, int s , int n)
{
	Vertex* start = findVertex(G, s);
	start->distance = 0;

	for (int i = 1; i <= n-1 ; i++)
	{
		
		Edge* e = G->eHead;
		while (e != NULL)
		{
			Vertex* u = findVertex(G, e->originVertex);
			Vertex* z = findVertex(G, e->destinationVertex);
			if (u->distance != INFINITY)// 이 조건이 있어야만 작동한다.
			{
				if (z->distance > u->distance + e->weight)// 이것만 있으면 70점 짜리
					z->distance = u->distance + e->weight;
			}

			e = e->next;
		}
	}


	Vertex* p = G->vHead;
	while (p != NULL)
	{
		if (p->name!=s && p->distance != INFINITY)
			printf("%d %d\n", p->name, p->distance);
		p = p->next;
	}
}
int main() {

	Graph G;
	initGraph(&G);
	int n, m, start;// n = 정점의 개수, m= 간선의 개수, start = 시작정점
	int weight, ori, dest;
	scanf("%d %d %d", &n, &m, &start);

	for (int i = 1; i <= n; i++)
	{
		insertVertex(&G, i);
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &ori, &dest, &weight);
		insertEdge(&G, ori, dest, weight);
	}
	BellmanFordShortestPaths(&G, start, n);


	return 0;
}