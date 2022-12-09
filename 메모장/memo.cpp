#include<stdio.h>

#include<stdlib.h>



struct node {

	int number;

	struct node* next;

};



struct node* hashTable;

int M;



int h(int x) {

	return x;

}



void insertItem(int x) {

	int v = h(x);

	struct node* p = hashTable + v;

	struct node* newnode = (struct node*)malloc(sizeof(struct node));

	newnode->number = x;

	newnode->next = NULL;

	if (p->next == NULL) {

		p->next = newnode;

	}

	else {

		newnode->next = p->next;

		p->next = newnode;

	}

}



int searchItem(int x) {

	int v = h(x), count = 0;

	struct node* p = hashTable + v;

	if (p->next == NULL) {

		return 0;

	}

	else {

		while (1) {

			p = p->next;

			count++;

			if (p->number == x) {

				return count;

			}

			if (p->next == NULL) {

				return 0;

			}

		}

	}

}



int deleteItem(int x) {

	int v = h(x), count = 0;

	struct node* pt = hashTable + v, * p = hashTable + v;

	if (p->next == NULL) {

		return 0;

	}

	else {

		while (1) {

			p = p->next;

			count++;

			if (p->number == x) {

				while (pt->next != p) {

					pt = pt->next;

				}

				pt->next = p->next;

				free(p);

				return count;

			}

			if (p->next == NULL) {

				return 0;

			}

		}

	}

}



void printTable() {

	struct node* p;

	for (int i = 0; i < M; i++) {

		p = hashTable + i;

		if (p->next != NULL) {

			p = p->next;

			printf(" %d", p->number);

			while (p->next != NULL) {

				p = p->next;

				printf(" %d", p->number);

			}

		}

	}

	printf("\n");

}



void freeTable() {

	struct node* p, * q;

	for (int i = 0; i < M; i++) {

		if ((hashTable + i)->next != NULL) {

			p = (hashTable + i)->next;

			q = p;

			while (q->next != NULL) {

				p = p->next;

				free(q);

				q = p;

			}

		}

	}

	free(hashTable);

}



void main() {

	int key;

	char select;

	scanf("%d", &M);

	hashTable = (struct node*)malloc(sizeof(struct node) * M);

	for (int i = 0; i < M; i++) {

		(hashTable + i)->number = NULL;

		(hashTable + i)->next = NULL;

	}

	while (1) {

		scanf("%c", &select);

		if (select == 'i') {

			scanf("%d", &key);

			insertItem(key);

			getchar();

		}

		else if (select == 's') {

			scanf("%d", &key);

			printf("%d\n", searchItem(key));

			getchar();

		}

		else if (select == 'd') {

			scanf("%d", &key);

			printf("%d\n", deleteItem(key));

			getchar();

		}

		else if (select == 'p') {

			printTable();

			getchar();

		}

		else if (select == 'e') {

			break;

		}

	}

	freeTable();

}