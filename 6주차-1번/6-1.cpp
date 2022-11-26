#include<stdio.h>
#include<stdlib.h>
int checkPoint, n;
void insertItem(int* A, int N)
{
	for (int i = 0; i < N; i++)// ют╥б
	{
		scanf("%d", &A[i]);
	}
}
int rFE(int* A, int k, int left, int right)
{

	if (left > right)// base case
	{
		if (A[checkPoint] < k)
			return checkPoint;
		if(checkPoint==n-1||checkPoint==0)
			return -1;
		return checkPoint;
	}

	int mid = (left + right) / 2;
	if (k == A[mid])
		return mid;
	else if (k < A[mid])
		return rFE(A, k, left, mid - 1);
	else if (k > A[mid])
	{
		checkPoint = mid;
		return rFE(A, k, mid + 1, right);
	}

}
void Print(int* A, int N)
{
	for (int i = 0; i < N; i++)
		printf(" %d", A[i]);
}
int findElement(int* A, int k, int N)
{
	return rFE(A, k, 0, N - 1);
}
int main()
{
	int k;

	scanf("%d %d", &n, &k);

	int* arr = (int*)malloc(sizeof(int) * n);
	insertItem(arr, n);


	printf("%d\n", findElement(arr, k, n));

	return 0;
}