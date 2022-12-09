#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// 개방주소법 해시테이블 - 선형조사법
int M;
#define NoSuchKey -1

typedef struct bucket
{
	int key;
	int empty;
}bucket;
void initBucketArray(bucket* A)
{
	for (int i = 0; i < M; i++)
	{
		A[i].empty = 0;
	}
	return;
}
int HashFunction(int x)
{
	return x % M;
}
bool isEmpty(bucket* b)
{
	return (b->empty == 0);
}
// linear probing
int getNextBucket(int v, int i)
{
	return (v + i) % M;
}
void overflowException()
{
	printf("overflowException\n");
	return;
}
void findElement(bucket* A, int key)
{
	int v = HashFunction(key);
	int i = 0;
	while (i < M)
	{
		int b = getNextBucket(v, i);
		if (isEmpty(&A[b]))
			i++;
		else if (key == A[b].key)
		{
			printf("%d %d\n", b, A[b].key);
			return;
		}
		else
			i++;
	}
	printf("%d\n", NoSuchKey);
	return;
}
void insertItem(bucket* A, int k)
{
	int v = HashFunction(k);
	int i = 0;
	while (i < M)
	{
		int b = getNextBucket(v, i);
		if (isEmpty(&A[b]))
		{
			A[b].key = k;
			A[b].empty = 1;
			printf("%d\n", b);
			return;
		}
		else
		{
			printf("C");
			i++;
		}
	}
	overflowException();
	return;
}
int main() {
	int n, id;
	char menu;
	scanf("%d %d", &M, &n);
	bucket* A = (bucket*)malloc(sizeof(bucket) * M);
	getchar();

	while (1)
	{
		scanf("%c", &menu);
		switch (menu)
		{
		case 'i':
			scanf("%d", &id);
			insertItem(A, id);
			break;
		case 's':
			scanf("%d", &id);
			findElement(A, id);
			break;
		case 'e':
			return 0;
		}
		getchar();
	}

	return 0;
}