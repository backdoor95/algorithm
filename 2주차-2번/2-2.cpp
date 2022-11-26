#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define FALSE 0// 이렇게 코딩하는 방식은 처음!
#define TRUE 1
/// 버블정렬
void BubbleSort(int* list, int n)
{
	//printf("<<<<<<<<<<<<<<<< BubbleSort >>>>>>>>>>>>>>\n\n");
	for (int i = n - 1; i > 0; i--)
	{
		int flag = FALSE;
		for (int j = 0; j < i; j++)
		{
			if (list[j] > list[j + 1])
			{
				int tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
			flag = TRUE;
		}

		if (flag == FALSE)//정렬 끝!!
			break;
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


	BubbleSort(list, n);

	for (int i = 0; i < n; i++)
		printf(" %d", list[i]);

	return 0;
}