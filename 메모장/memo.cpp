#include<stdio.h>
#include<stdlib.h>
int main() {
	int k = 0;
	int** arr;
	int n;
	scanf("%d", &n);

	arr = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = (int*)malloc(sizeof(int) * n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = k;
			k++;
		}
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", arr[i][j]);// *(*(arr+i)+j)
			
		}
		printf("\n");
	}
	printf("\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", *(*(arr + i) + j));// *(*(arr+i)+j)

		}
		printf("\n");
	}

	return 0;
}