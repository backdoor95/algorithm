#include<stdio.h>
#include<stdlib.h>
#define HEAP_SIZE 100
int H[HEAP_SIZE];
int n=0;
int element(int v)
{
	return H[v];
}
int root()
{
	return 1;
}
int isRoot(int v) {
	return v == 1;
}
int parent(int v)
{
	return (v / 2);
}
int leftChild(int v)
{
	return (2 * v);
}
int rightChild(int v)
{
	return (2 * v + 1);
}
int even(int v)
{
	return (v % 2 == 0);
}
int sibling(int v)
{
	if (even(v))
		return v + 1;
	else
		return v - 1;
}
int isInternal(int v)
{
	return ((2 * v < HEAP_SIZE) && (H[2 * v] != NULL));
}
int isExternal(int v)
{
	return ((2 * v >= HEAP_SIZE) || (H[2 * v] == NULL));
}
void swapElements(int child, int parent)
{
	int tmp = H[child];
	H[child] = H[parent];
	H[parent] = tmp;
}
void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}
void UpHeap(int v)
{
	if (v == 1)
		return;
	if (H[v] <= H[parent(v)])
		return;
	swapElements(v, parent(v));
	UpHeap(parent(v));
}
void advanceLast()
{
	n++;
}
void insertItem(int key)
{
	advanceLast();
	int z = n;
	H[z] = key;
	UpHeap(z);
	printHeap();
}

void downHeap(int v)
{
	if (isExternal(leftChild(v)) && isExternal(rightChild(v)))
		return;
	int bigger = leftChild(v);// bigger는 자식노드
	if (isInternal(rightChild(v)))
		if (H[rightChild(v)] > H[bigger])
			bigger = rightChild(v);
	if (H[v] >= H[bigger])
		return;
	swapElements(v, bigger);
	downHeap(bigger);
}
void retreatLast()
{
	n--;
}
int removeMax()
{
	int k = H[1];
	H[1] = H[n];
	retreatLast();
	downHeap(root());
	//printHeap();
	return k;
}

int main() {
	char menu;
	int key;
	while (1)
	{
		scanf("%c", &menu);
		switch (menu)
		{
		case 'i':
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			break;
		case 'd':
			printf("%d\n", removeMax());
			break;
		case 'p':
			printHeap();
			break;
		case 'q':
			return 0;
			
		}
		getchar();
	}
	return 0;
}