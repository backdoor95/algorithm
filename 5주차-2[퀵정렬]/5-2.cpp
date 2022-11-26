#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SWAP(x, y){int t = x;x=y;y=t;}
void Print(int* List, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", List[i]);
	}
	printf("\n");
}
int inPlacePartition(int* L, int left, int right, int k)
{
	int pivot, tmp, low, high;
	pivot = L[k];
	SWAP(L[k], L[right]);
	low = left;
	high = right - 1;
	while (low <= high)
	{
		while (low <= high && L[low] <= pivot)
			low++;
		while (low <= high && L[high] >= pivot)
			high--;
		if (low < high)
			SWAP(L[low], L[high]);
	}
	SWAP(L[low], L[right]);
	return low;
}
void inPlaceQuickSort(int* L, int left, int right)
{
	if (left > right)return;
	int k = rand() % (right - left + 1) + left;
	int q = inPlacePartition(L, left, right, k);
	inPlaceQuickSort(L, left, q - 1);
	inPlaceQuickSort(L, q + 1, right);
}
int main() {
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	int* L = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &L[i]);
	inPlaceQuickSort(L, 0, n - 1);
	Print(L, n);

	return 0;
}