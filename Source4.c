#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int coeff;
	int exp;
	Position next;
}polinom;


Position createPolinom(int, int);
void insertEnd(Position, Position);
void printList(Position);
void sumPolinom(Position, Position, Position);
void readFile(char* fileName,Position,Position);

int main() {
	FILE* File;
	Position P = NULL;
	Position Q = NULL;
	polinom head1;
	polinom head2;
	polinom head3;
	head1.next = NULL;
	head2.next = NULL;
	head3.next = NULL;
	int coeff = 0, exp = 0;
	char fileName[256];
	printf("Insert file name: ");
	scanf("%s",fileName);
	
	readFile(fileName,&head1,&head2);

	printf("\nList1 content:\n\tcoeff\texp\n");
	printList(&head1);
	printf("\nList2 content:\n\tcoeff\texp\n");
	printList(&head2);

	sumPolinom(&head1, &head2, &head3);
	printf("\nSum of polinoms list content:\n\tcoeff\texp\n");
	printList(&head3);

	return 0;
}

Position createPolinom(int coeff, int exp) {
	Position K = NULL;

	K = (Position)malloc(sizeof(polinom));
	if (!K)
		printf("Memory failed to allocate!");

	K->coeff = coeff;
	K->exp = exp;
	K->next = NULL;

	return K;
}


void insertEnd(Position head, Position K) {
	while (head->next != NULL)
		head = head->next;
	
	K->next = head->next;
	head->next = K;
}

void readFile(char* fileName,Position head1,Position head2) {
	Position P=NULL;
	Position Q=NULL;
	int coeff = 0, exp = 0;

	FILE* File;
	File = fopen(fileName, "r");
	if (!File)
		printf("File failed to open!");
	char c;
	while (!feof(File))
	{
		c = fgetc(File);
		if (c != '\n') {
			fscanf(File, "%d %d", &coeff, &exp);
			P = createPolinom(coeff, exp);
			insertEnd(head1, P);
		}
		else {
			while (!feof(File)) {
				fscanf(File, "%d %d", &coeff, &exp);
				Q = createPolinom(coeff, exp);
				insertEnd(head2, Q);
			}
		}
	}
}

void sumPolinom(Position P, Position Q, Position head3) {
	Position S = NULL;
	P = P->next;
	Q = Q->next;
	int coeff = 0;

	while (P != NULL || Q != NULL) {
		if (P == NULL)
			break;
		if (Q == NULL)
			break;
		if (P->exp == Q->exp) {
			coeff = P->coeff + Q->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, P->exp);
				insertEnd(head3, S);
			}
			P = P->next;
			Q = Q->next;
		}
		else if (P->exp < Q->exp) {
			coeff = P->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, P->exp);
				insertEnd(head3, S);
			}
			P = P->next;
		}
		else {
			coeff = Q->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, Q->exp);
				insertEnd(head3, S);
			}
			Q = Q->next;
		}
	}
	if (P == NULL) {
		while (Q != NULL) {
			coeff = Q->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, Q->exp);
				insertEnd(head3, S);
			}
			Q = Q->next;
		}
	}
	if (Q == NULL) {
		while (P != NULL) {
			coeff = P->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, P->exp);
				insertEnd(head3, S);
			}
			P = P->next;
		}
	}
}

void printList(Position head) {
	
	Position K = NULL;
	
	if (head->next == NULL)
		printf("Linked list is empty");
	
	K = head->next;
	while (K != NULL) {
		printf("\t%d\t%d\n", K->coeff, K->exp);
		K = K->next;
	}

	puts("\n");
}