#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
//선택정렬
void swap(int* list, int i, int min)
{
	int temp = list[min];
	list[min] = list[i];
	list[i] = temp;
}
void selectionSort(int* list, int n)
{
	//	printf("<<<<<<<<<<<<<<<< SelectionSort >>>>>>>>>>>>>>\n\n");
	for (int i = 0; i <= n - 2; i++)
	{
		int min = i;// 입력값을 위한 O(1) 임... 문제조건
		for (int j = i + 1; j <= n - 1; j++)
		{
			if (list[j] < list[min])
				min = j;
		}
		swap(list, i, min);
		/*printf(" %d Pass >> ", i + 1);
		for (int i = 0; i < n; i++) {
			printf("%d ", list[i]);
		}
		printf("\n");*/

	}

}
int main() {

	int n;
	int* list;

	scanf("%d", &n);
	list = (int*)malloc(sizeof(int) * n);

	//srand(time(NULL));// seed rand
	//for (int i = 0; i < n; i++) {
	//	list[i] = rand() % 100;
	//}
	//printf("Before Sort : ");
	//for (int i = 0; i < n; i++) {
	//	printf("%d ", list[i]);
	//}
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}


	selectionSort(list, n);

	for (int i = 0; i < n; i++)
		printf(" %d", list[i]);

	return 0;
}