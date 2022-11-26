#include<stdio.h>
#include<stdlib.h>
int rFindElement(int arr[], int left, int right, int k)
{

	int mid;

	if(left <= right)
	{
		mid = (left + right) / 2;

		if (arr[mid] == k)
			return mid;
		else if (arr[mid] > k)
			return rFindElement(arr, left, mid - 1, k);
		else
			left = mid + 1;
	}
	return -1;
}
int iFindElement(int arr[], int n, int k)
{
	int left = 0;
	int right = n - 1;
	int mid;

	while(left <= right)
	{
		mid = (left + right) / 2;

		if (arr[mid] == k)
			return mid;
		else if (arr[mid] > k)
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int *arr = (int*)malloc(sizeof(int)*n);
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("%d\n", rFindElement(arr, 0, n, k));
	//printf("%d\n", iFindElement(arr, n, k));


	return 0;
}