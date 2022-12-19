#include<stdio.h>
#include<stdlib.h>
int n, m;
int topOrder[100];

typedef struct Edge
{
	int originVertexIndex;
	int destinationVertexIndex;
}Edge;
typedef struct IncidentEdge
{
	int element;
	struct IncidentEdge* next;
}IncidentEdge;
typedef struct Vertex
{
	char name;
	IncidentEdge* outEdges;
	IncidentEdge* inEdges;
	int inDegree;
}Vertex;
typedef struct Graph
{
	Vertex* vertices;
	Edge* edges;
}Graph;
Graph G;
Vertex* findVertex(Graph* G, char VertexName)
{
	Vertex* p = G->vertices;
	for (int i = 0; i < n; i++)
	{
		if (p[i].name == VertexName)
		{
			return p;
		}
	}
}
int index(char vName)
{
	for (int i = 0; i < n; i++)
	{
		if (G.vertices[i].name == vName)
			return i;
	}
}
void addFirst(IncidentEdge* H, int i)
{
	IncidentEdge* node = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	node->element = i;
	
	node->next = H->next;
	H->next = node;
}
void insertDirectedEdge(char uName, char wName, int i)
{

	int u = index(uName);// 출발
	int w = index(wName);// 도착

	G.edges[i].originVertexIndex = u;
	G.edges[i].destinationVertexIndex = w;
	addFirst(G.vertices[u].outEdges, i);
	addFirst(G.vertices[w].inEdges, i);
	G.vertices[w].inDegree++;//정점 진입차수 갱신
}
void insertVertex(char vName, int i)
{
	G.vertices[i].name = vName;
	G.vertices[i].outEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge));// 헤더노드 생성
	G.vertices[i].outEdges->next = NULL;
	G.vertices[i].inEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge));// 헤더노드 생성
	G.vertices[i].inEdges->next = NULL;
	G.vertices[i].inDegree = 0;
}
void initializerGraph()
{
	G.edges = NULL;
	G.vertices = NULL;
}
void buildGraph()
{
	initializerGraph();
	char c;
	char v1, v2;
	scanf("%d", &n);
	getchar();
	G.vertices = (Vertex*)malloc(sizeof(Vertex)*n);
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &c);
		getchar();
		insertVertex(c, i);
	}

	scanf("%d", &m);
	getchar();
	G.edges = (Edge*)malloc(sizeof(Edge) * m);
	for (int i = 0; i < m; i++)
	{
		scanf("%c %c", &v1, &v2);
		getchar();
		insertDirectedEdge(v1, v2, i);
	}
}

/////////// Que 연관함수 //////////
typedef struct queNode
{
	Vertex v;
	struct queNode* next;
}queNode;
typedef struct Que
{
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
queNode* getQueNode() {
	queNode* q = (queNode*)malloc(sizeof(queNode));
	q->next = NULL;
	return q;
}
void freeQueNode(queNode* q)
{
	free(q);
	q = NULL;
}
void enqueue(Que* Q, Vertex v)
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
int dequeue(Que* Q)
{
	if (isEmpty(Q))
	{
		printf("Que is Empty!!\n");
	}
	queNode* p = Q->f;
	char element = p->v.name;
	Q->f = Q->f->next;
	if (Q->f == NULL)
		Q->r = NULL;
	freeQueNode(p);
	int VertexIndex = index(element);
	return VertexIndex;
}
void topologicalSort()// 위상 정렬 알고리즘
{
	Que Q;
	initQue(&Q);
	int* in = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		in[i] = G.vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(&Q, G.vertices[i]);
	}
	int t = 1;
	while (!isEmpty(&Q))
	{
		int u = dequeue(&Q);// 정점배열의 인덱스
		topOrder[t] = u;
		t = t + 1;
		IncidentEdge* p = G.vertices[u].outEdges;
		p = p->next;
		while (p != NULL)
		{
			int w = G.edges[p->element].destinationVertexIndex;
			in[w] = in[w] - 1;
			if (in[w] == 0)
				enqueue(&Q, G.vertices[w]);
			p = p->next;
		}
		
	}

	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}
int main() {

	buildGraph();

	topologicalSort();
	
	if (topOrder[0] == 0)
		printf("0");
	else
	{
		for (int i = 1; i <= n; i++)
		{
			printf("%c ", G.vertices[topOrder[i]].name);
		}
	}
	return 0;
}