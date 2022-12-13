#include<stdio.h>
#include<stdlib.h>
typedef struct Edge// 간선
{
	int weight;
	int v1, v2;// 간선 양 옆에 있는 정점노드의 숫자
	struct Edge* next;
}Edge;
typedef struct IncidentEdge// 인접리스트
{
	int adjacentVertex;// 인접 정점
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;
typedef struct Vertex// 정점
{
	int nodeNumber;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;
typedef struct
{
	Vertex* vHead;
	Edge* eHead;
}Graph;
void initGraph(Graph* G)
{
	G->vHead = NULL;// 정점
	G->eHead = NULL;// 간선
}
void insertIncidentEdge(Vertex* v, Edge* e, int VertexNumber)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->adjacentVertex = VertexNumber;
	p->e = e;
	p->next=NULL;
	IncidentEdge* q = v->iHead;// q 는 v에 속함.
	if (q == NULL)// 첫 노드 일때
	{
		v->iHead = p;
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
Vertex* insertVertex(Graph *G, int vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->nodeNumber = vName;
	v->iHead = NULL;// 인접리스트
	v->next = NULL;// 다음 정점
	Vertex* q = G->vHead;
	
	if (q == NULL)// 첫 노드 일때
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
	e->v1 = v1->nodeNumber;
	e->v2 = v2->nodeNumber;
	e->next = NULL;

	Edge* q = G->eHead;
	if (q == NULL)// 첫 노드 일떄
		G->eHead = e;
	else
	{
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = e;
	}

	if (v1->nodeNumber == v2->nodeNumber)// 출발지와 목적지가 같을때
	{
		insertIncidentEdge(v1, e, v1->nodeNumber);
	}
	else 
	{
		insertIncidentEdge(v1, e, v2->nodeNumber);
		insertIncidentEdge(v2, e, v1->nodeNumber);
	}
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
	Vertex* x = findVertex(G, v1);
	Vertex* y = findVertex(G, v2);

	//a 또는 b가 존재하지 않을때 -1를 출력
	if (x == NULL || y == NULL)
	{
		printf("%d\n", -1);
		return;
	}

	//weight = 0 이면 간선을 삭제한다.
	if (weight == 0)
	{
		Edge* E = NULL;
		//1. v1의 incident list에서 해당 노드를 삭제한다.
		Vertex* p = findVertex(G, v1);
		IncidentEdge* q = p->iHead;
		IncidentEdge* r = p->iHead;
		while (q != NULL)
		{

			if (q->adjacentVertex == v2)// 간선을 찾았을때
			{
				E = q->e;// 간선을 지우기 위한 변수
				if (q == p->iHead)
				{
					p->iHead = q->next;
					free(q);
					break;
				}
				else
				{
					r->next = q->next;
					free(q);
					break;
				}
				
			}
			r = q;
			q = q->next;
		}

		//2. v2의 incident list에서 해당 노드를 삭제한다.
		p = findVertex(G, v2);
		q = p->iHead;
		r = p->iHead;
		while (q != NULL)
		{

			if (q->adjacentVertex == v1)// 간선을 찾았을때
			{
				if (q == p->iHead)
				{
					p->iHead = q->next;
					free(q);
					break;
				}
				else
				{
					r->next = q->next;
					free(q);
					break;
				}
				
			}
			r = q;
			q = q->next;
		}
		//3. edge list 에서 해당 간선노드 삭제
		Edge* k = G->eHead;
		Edge* m = G->eHead;
		if (E==G->eHead)
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

		// 4.반환
		return;
	}//끝

	// 간선을 찾아서 간선을 변경
	Vertex* p = findVertex(G, v1);
	IncidentEdge* q = p->iHead;
	while (q != NULL)
	{

		if (q->adjacentVertex == v2)// 간선을 찾았을때
		{
			q->e->weight = weight;
			return;
		}
		q = q->next;
	}
	// 간선이 존재하지 않을때
	// 간선을 생성
	insertEdge(G, x, y, weight);
	return;
}
void Print_AdjacentAndWeight(Graph*G,int nodeNumber)
{
	Vertex* p = findVertex(G, nodeNumber);
	if (p == NULL)
	{
		printf("%d\n", -1);
		return;
	}
	IncidentEdge* q = p->iHead;
	for (int i = 1; i <= 6; i++)
	{
		q = p->iHead;
		while (q != NULL)
		{
			if (i == q->adjacentVertex)
				printf(" %d %d", i, q->e->weight);
			q = q->next;
		}
	}
	printf("\n");
}
void print(Graph *G)
{
	/*Vertex* p = G->vHead;
	while (p != NULL)
	{
		printf("node number = %d\n", p->nodeNumber);
		p = p->next;
	}*/
	/*Vertex* p = findVertex(G, 3);
	IncidentEdge* q = p->iHead;
	while (q != NULL)
	{
		printf("adjacent node number = %d\n", q->adjacentVertex);
		q = q->next;
	}*/
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

	//print(&G);

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