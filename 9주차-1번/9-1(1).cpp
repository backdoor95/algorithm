#include<stdio.h>	
#include<stdlib.h>
int M;
typedef struct HashNode {
	int key;
	struct HashNode* next;
}HashNode;
int HashFunction(int k)
{
	return (k % M);
}
void initBucketArray(HashNode* h)
{
	for (int i = 0; i < M; i++)
	{
		h[i].key = 0;
		h[i].next = NULL;
	}
}
void insertItem(HashNode* h, int k)
{
	int v = HashFunction(k);
	HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
	newNode->key = k;
	newNode->next = h[v].next;
	h[v].next = newNode;
}
int findElement(HashNode* h,int k)
{
	int count = 0;
	int v = HashFunction(k);
	HashNode* p = &h[v];
	while (p->next != NULL)
	{
		p = p->next;
		count++;
		if (p->key == k)
		{
			return count;
		}
	}
	return 0;
}
int removeElement(HashNode* h, int k)
{
	int v = HashFunction(k);
	int count = 0;
	HashNode* p = &h[v];
	HashNode* q;
	while (p->next != NULL)
	{
		count++;
		if (p->next->key== k)
		{
			q = p->next;// 이 부분 수정
			p->next = q->next;
			free(q);
			return count;
		}
		p = p->next;
	}
	return 0;
}
void PrintHash(HashNode* h)
{
	HashNode* p;
	for (int i = 0; i < M; i++)
	{
		p = &h[i];
		while (p->next != NULL)
		{
			p = p->next;
			printf(" %d", p->key);
		}
	}
	printf("\n");
}
int main() {
	// 분리연쇄법

	char menu;
	int key;
	scanf("%d", &M);
	getchar();
	HashNode* HashArray = (HashNode*)malloc(sizeof(HashNode) * M);
	initBucketArray(HashArray);

	while (1)
	{
		scanf("%c", &menu);
		
		switch (menu)
		{
		case 'i':
			scanf("%d", &key);
			
			insertItem(HashArray, key);
			break;
		case 's':
			scanf("%d", &key);
			printf("%d\n",findElement(HashArray, key));
			break;
		case 'd':
			scanf("%d", &key);
			printf("%d\n", removeElement(HashArray, key));
			break;
		case 'p':
			PrintHash(HashArray);
			break;
		case 'e':
			return 0;

		}
		getchar();
	}
	return 0;

}