#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
typedef struct
{
	int H[SIZE];
	int n;
}Heap;
void init(Heap* heap)
{
	for (int i = 0; i < SIZE; i++)
	{
		heap->H[i] = 0;
	}
	heap->n = 0;
}
void printHeap(Heap* heap)
{
	for (int i = 1; i <= heap->n; i++)
	{
		printf(" %d", heap->H[i]);
	}
	printf("\n");
}
void upHeap(Heap* heap)
{
	int i = heap->n;
	int k = heap->H[i];
	while ((i != 1) && (k > heap->H[i / 2]))
	{
		heap->H[i] = heap->H[i / 2];
		i /= 2;
	}
	heap->H[i] = k;
}
void insertItem(Heap* heap, int k)
{
	heap->n++;
	heap->H[heap->n] = k;
	upHeap(heap);
	printHeap(heap);
}
void downHeap(Heap* heap)
{
	int temp = heap->H[1];
	int p = 1, c = 2;// p 부모, c 자식
	while (c <= heap->n)// 자식이 있으면 진행
	{
		if ((c < heap->n) && (heap->H[c] < heap->H[c + 1]))// 형제노드가 있다는 의미
			c++;
		if (temp >= heap->H[c])
			break;
		heap->H[p] = heap->H[c];

		p = c;
		c *= 2;
	}
	heap->H[p] = temp;
}
int removeMax(Heap* heap)
{
	int k = heap->H[1];// index 1 에는 항상 최대값 [ 최대힙 ]
	heap->H[1] = heap->H[heap->n];// 마지막 노드값을 첫번째 자리로 옮김.
	heap->n--;// 전체 수 줄이기
	downHeap(heap);
	return k;
}

int main() {
	Heap heap;
	init(&heap);
	char menu;
	int key;

	while (1)
	{
		scanf("%c", &menu);
		switch (menu)
		{
		case 'i':
			scanf("%d", &key);

			insertItem(&heap, key);
			printf("0\n");
			//printHeap(&heap);
			break;

		case 'd':
			printf("%d\n", removeMax(&heap));
			//printHeap(&heap);
			break;
		case 'p':
			printHeap(&heap);
			break;
		case 'q':
			return 0;


		}
		getchar();
	}
	return 0;
}