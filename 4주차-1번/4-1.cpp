#include<stdio.h>
#include<stdlib.h>
#define HEAP_SIZE 100
int H[HEAP_SIZE];
int n=0;
int root()
{
	return 1;
}
int isRoot(int v)
{
	return v == 1;
}
int parent(int v)
{
	return(v / 2);
}
int leftChild(int v)
{
	return (2 * v);
}
int rightChild(int v)
{
	return (2 * v + 1);
}
void swapElements(int child, int parent)
{
	int tmp = H[child];
	H[child] = H[parent];
	H[parent] = tmp;
}
void printHeap()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}
void UpHeap(int v)
{
	if (isRoot(v))
		return;
	if (H[v] <= parent(v))
		return;
	swapElements(v, parent(v));
	UpHeap(parent(v));
}
void advanceLast()// 전진
{
	n++;
}
void insertItem(int key)
{
	advanceLast();
	H[n] = key;
	UpHeap(n);
}
void downHeap(int v)
{
	if (leftChild(v) > n)
		return;
	int greater = leftChild(v);
	if (rightChild(v) <= n)
		if (H[rightChild(v)] > H[greater])
			greater = rightChild(v);

	if (H[v] >= H[greater])
		return;
	swapElements(v, greater);
	downHeap(greater);
}
void rBuildHeap(int i)// 재귀적 상향식
{
	if (i > n)
		return;
	rBuildHeap(2 * i);// 좌 subtree
	rBuildHeap(2 * i + 1);// 우 subtree
	downHeap(i);
}
void buildHeap()
{
	for (int i = n / 2; i >= 1; i--)
	{
		downHeap(i);
	}
}
void retreatLast()
{
	n--;
}
void printArray()
{
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}

void inPlaceHeapSort()
{
	buildHeap();// 1기
	
	int n2 = n;
	for (int i = n; i >= 2; i--)
	{
		int tmp = H[1];
		H[1] = H[i];
		H[i] = tmp;
		n--;
		downHeap(1);
	}
	n = n2;
	printArray();
	
}


int main() {
	int num;
	int key;

	scanf("%d", &num);
	n = num;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &H[i]);
	}
	inPlaceHeapSort();

}