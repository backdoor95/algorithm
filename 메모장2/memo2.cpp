#include<stdio.h>
#include<stdlib.h>

void func2(int* v1, int* v2)
{
	printf(" v1 가 저장하고 있는 주소 = %p\n", v1);
	printf(" v2 가 저장하고 있는 주소 = %p\n", v2);
	printf("\n\n");
}
void func1(int* v1, int* v2)
{
	printf(" v1 가 저장하고 있는 주소 = %p\n", v1);
	printf(" v2 가 저장하고 있는 주소 = %p\n", v2);
	printf("\n\n");
	func2(v1, v2);
}
int main() {

	int n = 4;

	int* v1 = &n;
	int* v2 = &n;

	printf(" v1 가 저장하고 있는 주소 = %p\n", v1);
	printf(" v2 가 저장하고 있는 주소 = %p\n", v2);
	printf("\n\n");
	func1(v1, v2);

	return 0;
}