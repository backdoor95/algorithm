#include<stdio.h>
#include<stdlib.h>
int recursive(int parent[], int x)
{
	if (parent[x] == x)return x;
	return parent[x] = recursive(parent, parent[x]);
}
int main() {
	int parent[10];
	for (int i = 0; i < 10; i++)
		parent[i] = i;


	return 0;
}