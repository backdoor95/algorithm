#include<stdio.h>
#include<stdlib.h>

int findNumber(int a, int b, int n, char* A)
{
	
	int m;
	for (int i = 0; i < n; i++)
	{
		m = (a + b) / 2;
		if (A[i] == 'Y')
		{
			a = m + 1;
		}
		else if (A[i] == 'N')
		{
			b = m;
		}
		if (a == b)return a;
	}
	
}
int main() {

	int a, b, n;
	scanf("%d %d %d", &a, &b, &n);
	getchar();
	char* A = (char*)malloc(sizeof(char) * (n + 1));
	scanf("%s", A);

	printf("%d", findNumber(a, b, n, A));
}