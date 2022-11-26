#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100

typedef struct
{
	int H[SIZE];
	int n;

}Heap;
void init(Heap* heap)
{
	heap->n = 0;
}

void upHeap(Heap* heap)
{
	int  i = heap->n;
	int k = heap->H[i];// key 값

	while ((i != 1) && (k < heap->H[i / 2]))
	{
		heap->H[i] = heap->H[i / 2];
		i /= 2;
	}
	heap->H[i] = k;


}
void insertItem(Heap* heap, int k)// 프로그램 작성할때 왠만해서는 전역으로 하지 말것..! 그러나 교재에서는 전역으로 프로그래밍을했다.
{
	heap->n++;
	heap->H[heap->n] = k;
	upHeap(heap);

}
void downHeap(Heap* heap)
{
	int temp = heap->H[1];
	int p = 1, c = 2;// p :부모, c: 자식
	while (c <= heap->n)
	{
		if ((c < heap->n) && (heap->H[c] > heap->H[c + 1]))// 형제노드가 있다는 의미
			c++;

		if (temp <= heap->H[c])
			break;
		heap->H[p] = heap->H[c];

		p = c;
		c *= 2;
	}
	heap->H[p] = temp;
}

int removeMin(Heap* heap)
{
	int k = heap->H[1];
	// 발생 가능한 에러는 처리를 해줘야함. 그러나 수업에서는 에러가 없을 것이라 가정
	heap->H[1] = heap->H[heap->n];
	heap->n--;
	downHeap(heap);
	return k;
}
void printHeap(Heap* heap)
{
	for (int i = 1; i <= heap->n; i++)
	{
		printf("%d ", heap->H[i]);
	}
	printf("\n");


}
int  main() {
	/// 힙과 힙 정렬

	// 힙 :  우선순위 큐를 위해 만들어진 자료구조
	// 힙은 배열로 함?
	// 트리를 배열로 만들지 않는 이유 : 한쪽으로 치우쳐지면 중간중간에 비어있을 확률이 많기 때문에 
	Heap heap;
	init(&heap);
	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		int k = rand() % 100;
		insertItem(&heap, k);
		printf("%d ", k);
	}
	printf("\n");
	getchar();// 잠깐씩 끊어서 출력하려고

	printHeap(&heap);
	getchar();

	printf("Min :  %d\n", removeMin(&heap));
	printHeap(&heap);

	return 0;

}
/*
////////////////////////
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
			getchar();
			insertItem(&heap, key);
			printf("0\n");
			break;

		case 'd':

		case 'p':
			printHeap(&heap);
			break;
		case 'q':
			return 0;
		default:
			return 0;

		}
	}
	return 0;
}
////////////////////////
*/