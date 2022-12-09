#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
// 개방주소법 해시테이블 - 이중해싱
int M, q, key;
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
		A[i].key = 0;
		A[i].empty = 0;
	}
	return;
}
int HashFunction_1(int x)
{
	return x % M;
}
int HashFunction_2(int x)
{
	return (q - (x % q));
}
bool isEmpty(bucket* b)
{
	return (b->empty == 0);
}
// double Hashing// 괄호 주의할것!
int getNextBucket(int v, int i)
{
	return (v + (i*HashFunction_2(key))) % M;
}
void overflowException()
{
	printf("overflowException\n");
	return;
}
void PrintHashTable(bucket*A)
{
	for (int i = 0; i < M; i++)
		printf(" %d", A[i]);
	printf("\n");
}
void findElement(bucket* A, int key)
{
	int v = HashFunction_1(key);
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
	int v = HashFunction_1(k);
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
	int n;
	char menu;
	scanf("%d %d %d", &M, &n, &q);
	bucket* A = (bucket*)malloc(sizeof(bucket) * M);
	getchar();
	while (1)
	{
		scanf("%c", &menu);
		switch (menu)
		{
		case 'i':
			scanf("%d", &key);
			insertItem(A, key);
			break;
		case 's':
			scanf("%d", &key);
			findElement(A, key);
			break;
		case 'p':
			PrintHashTable(A);
			break;
		case 'e':
			PrintHashTable(A);
			return 0;
		}
		getchar();
	}
}