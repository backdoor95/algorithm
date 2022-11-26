#include<stdio.h>
#include<stdlib.h>
#define HEAP_SIZE 100
int H[HEAP_SIZE];
int n = 0;
int element(int v)
{
	return H[v];
}
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
	return (v / 2);
}
int leftChild(int v)
{
	return(2 * v);
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
	return((v <= n) && (H[v] != NULL));
}
int isExternal(int v)
{
	return ((v > n) || H[v] == NULL);
}
//int isInternal(int v) // 내가 틀렸던 코드임 위에.. 약간 논리적으로 조금 이상함.
//{
//	return ((2 * v < HEAP_SIZE) && (H[2 * v] != NULL));
//}
//int isExternal(int v)
//{
//	return ((2 * v >= HEAP_SIZE) || (H[2 * v] == NULL));
//}
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
	H[n] = key;
	UpHeap(n);
}
void downHeap(int v)
{
	/*if (isExternal(leftChild(v)) && isExternal(rightChild(v)))
		return;*/
	if (leftChild(v) > n)
		return;
	int bigger = leftChild(v);
	/*if(isInternal(rightChild(v)))
		if(H[rightChild(v)] > H[bigger])
			bigger= rightChild(v);*/
	if (rightChild(v) <= n)
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
	int k = H[root()];
	H[root()] = H[n];
	retreatLast();
	downHeap(root());
	return k;
}
void rBuildHeap(int i)// 재귀적 상향식
{
	if (i > n)
		return;
	rBuildHeap(2 * i);// 좌 부트리
	rBuildHeap(2 * i + 1);// 우 부트리
	downHeap(i);
}
void buildHeap()// 비재귀적 상향식
{
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
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
	//1. 비재귀적 상향식
	buildHeap();
	printHeap();

	//2. 재귀적 상향식
	/*rBuildHeap(1);
	printHeap();*/

	return 0;
}