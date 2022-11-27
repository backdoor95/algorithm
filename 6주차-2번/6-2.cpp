#include<stdio.h>
#include<stdlib.h>
int n, checkPoint=-1;
void insertItem(int* A, int N)
{
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &A[i]);

	}
}
int findElement(int* A,int left, int right, int key)
{

	int mid = (left + right) / 2;
	while (left <= right)
	{
		mid = (left + right) / 2;

		if (key == A[mid])
			return mid;
		else if (key < A[mid])
		{
			checkPoint = mid;
			right = mid - 1;
		}
		else if (key > A[mid])
			left = mid + 1;;
	}
	if (checkPoint == -1)return n;
	else return checkPoint;
}
int main()
{	
	int k;
	scanf("%d %d", &n, &k);
	int* A = (int*)malloc(sizeof(int) * n);
	insertItem(A, n);
	printf(" %d\n",findElement(A,0, n-1, k));
	
	return 0;
}