
#include<stdio.h>
#include<stdlib.h>
#define N 6
//adjacency matrix
typedef struct Vertex
{
	int nodeNumber;
	struct Vertex* next;
}Vertex;
typedef struct Edge
{
	int weight;
	Vertex* v1, * v2;
	struct Edge* next;
}Edge;
typedef struct Graph
{
	Vertex* vHead;
	Edge* eHead;
	Edge*AdjMatrix[N][N];
}Graph;
void initGraph(Graph* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
	//Edge*p = (G->AdjMatrix[N][N]);
	//p = (Edge***)malloc(sizeof(Edge**) * 6);// 정점의 개수
	//for (int i = 0; i < 6; i++)
	//{
	//	p[i] = (Edge**)malloc(sizeof(Edge*) * 6);
	//}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			G->AdjMatrix[i][j] = NULL;
	}

	return;
}
Vertex* insertVertex(Graph* G, int nodeNumber)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->nodeNumber = nodeNumber;
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
void insertEdge(Graph* G, Vertex* v1, Vertex* v2, int weight)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = weight;
	e->v1 = v1;
	e->v2 = v2;
	e->next = NULL;

	Edge* q = G->eHead;
	if (q == NULL)
		G->eHead = e;
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = e;
	}
	
	int i = v1->nodeNumber - 1;
	int j = v2->nodeNumber - 1;
	G->AdjMatrix[i][j] = e;
	G->AdjMatrix[j][i] = e;
}
Vertex* findVertex(Graph* G, int nodeNumber)
{
	Vertex* p = G->vHead;
	while (p->nodeNumber != nodeNumber)
	{

		p = p->next;
		if (p == NULL)// 해당 정점을 찾지 못했을때
			break;

	}
	return p;
}
void modifyWeight(Graph* G, int v1, int v2, int weight)
{
	//a 또는 b가 존재하지 않을때 -1를 출력
	if (v1 > 6 || v2 > 6)
	{
		printf("%d\n", -1);
		return;
	}

	
	//weight = 0 이면 간선을 삭제한다.
	if (weight == 0)
	{
		Edge* E = G->AdjMatrix[v1 - 1][v2 - 1];
		G->AdjMatrix[v1 - 1][v2 - 1] = NULL;
		G->AdjMatrix[v2 - 1][v1 - 1] = NULL;
		//edge list 에서 해당 간선노드 삭제
		Edge* k = G->eHead;
		Edge* m = G->eHead;
		if (E == G->eHead)
		{
			G->eHead = E->next;
			free(E);
		}
		else
		{
			while (E != k)
			{
				m = k;
				k = k->next;
			}
			m->next = k->next;
			free(k);
		}
		return;
	}
	
	Edge* z = G->AdjMatrix[v1 - 1][v2 - 1];
	if (z == NULL)// 간선이 없을때, 간선을 생성한다.
	{
		Vertex* VV1 = findVertex(G, v1);
		Vertex* VV2 = findVertex(G, v2);
		insertEdge(G, VV1, VV2, weight);

	}
	else// 간선을 찾아서 간선을 변경
	{
		z->weight = weight;
	}
	return;

}
void Print_AdjacentAndWeight(Graph* G, int nodeNumber)
{
	
	if (nodeNumber > 6)
	{
		printf("%d\n", -1);
		return;
	}
	for (int i = 0; i < 6; i++)
	{
		if (G->AdjMatrix[nodeNumber - 1][i] != NULL)
			printf(" %d %d", i+1, G->AdjMatrix[nodeNumber - 1][i]->weight);
	}
	printf("\n");
}
int main() {
	char menu;
	int num, v1, v2, weight;
	Graph G;
	initGraph(&G);
	Vertex* a, * b, * c, * d, * e, * f;
	a = insertVertex(&G, 1);
	b = insertVertex(&G, 2);
	c = insertVertex(&G, 3);
	d = insertVertex(&G, 4);
	e = insertVertex(&G, 5);
	f = insertVertex(&G, 6);

	insertEdge(&G, a, b, 1);
	insertEdge(&G, a, c, 1);
	insertEdge(&G, a, d, 1);
	insertEdge(&G, a, f, 2);
	insertEdge(&G, b, c, 1);
	insertEdge(&G, c, e, 4);
	insertEdge(&G, e, e, 4);
	insertEdge(&G, e, f, 3);

	while (1)
	{
		scanf("%c", &menu);
		switch (menu)
		{
		case 'a':
			scanf("%d", &num);
			Print_AdjacentAndWeight(&G, num);
			break;
		case 'm':
			scanf("%d %d %d", &v1, &v2, &weight);
			modifyWeight(&G, v1, v2, weight);
			break;
		case 'q':
			return 0;
			break;
		}
		getchar();
	}
	
	return 0;
}