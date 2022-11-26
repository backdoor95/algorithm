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
	int k = heap->H[i];// key ��

	while ((i != 1) && (k < heap->H[i / 2]))
	{
		heap->H[i] = heap->H[i / 2];
		i /= 2;
	}
	heap->H[i] = k;


}
void insertItem(Heap* heap, int k)// ���α׷� �ۼ��Ҷ� �ظ��ؼ��� �������� ���� ����..! �׷��� ���翡���� �������� ���α׷������ߴ�.
{
	heap->n++;
	heap->H[heap->n] = k;
	upHeap(heap);

}
void downHeap(Heap* heap)
{
	int temp = heap->H[1];
	int p = 1, c = 2;// p :�θ�, c: �ڽ�
	while (c <= heap->n)
	{
		if ((c < heap->n) && (heap->H[c] > heap->H[c + 1]))// ������尡 �ִٴ� �ǹ�
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
	// �߻� ������ ������ ó���� �������. �׷��� ���������� ������ ���� ���̶� ����
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
	/// ���� �� ����

	// �� :  �켱���� ť�� ���� ������� �ڷᱸ��
	// ���� �迭�� ��?
	// Ʈ���� �迭�� ������ �ʴ� ���� : �������� ġ�������� �߰��߰��� ������� Ȯ���� ���� ������ 
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
	getchar();// ��� ��� ����Ϸ���

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