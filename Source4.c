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
void multPolinom(Position, Position, Position);
void Sort(int, int, Position);
void sortMult(Position);

int main() {
	FILE* File;
	Position P = NULL, Q = NULL;
	polinom head1, head2, head3, head4;
	head1.next = NULL, head2.next = NULL, head3.next = NULL, head4.next = NULL;
	int coeff = 0, exp = 0;
	int* sumCoeff, * sumExp;
	char fileName[256];
	printf("Insert file name (including .txt extension): ");
	scanf("%s", fileName);

	readFile(fileName, &head1, &head2);

	printf("\nList1 content:\n\tcoeff\texp\n");
	printList(&head1);
	printf("\nList2 content:\n\tcoeff\texp\n");
	printList(&head2);

	sumPolinom(&head1, &head2, &head3);
	printf("\nSum of polinoms list content:\n\tcoeff\texp\n");
	printList(&head3);

	multPolinom(&head1, &head2, &head4);
	printf("\nMultiplication of polinoms list content:\n\tcoeff\texp\n");
	printList(&head4);

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
	Position P = NULL, Q = NULL;
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
			Sort(coeff, exp, head1);
		}
		else {
			while (!feof(File)) {
				fscanf(File, "%d %d", &coeff, &exp);
				Sort(coeff, exp, head2);
			}
		}
	}
}

void sumPolinom(Position P, Position Q, Position head) {
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
				insertEnd(head, S);
			}
			P = P->next;
			Q = Q->next;
		}
		else if (P->exp < Q->exp) {
			coeff = P->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, P->exp);
				insertEnd(head, S);
			}
			P = P->next;
		}
		else {
			coeff = Q->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, Q->exp);
				insertEnd(head, S);
			}
			Q = Q->next;
		}
	}
	if (P == NULL) {
		while (Q != NULL) {
			coeff = Q->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, Q->exp);
				insertEnd(head, S);
			}
			Q = Q->next;
		}
	}
	if (Q == NULL) {
		while (P != NULL) {
			coeff = P->coeff;
			if (coeff != 0) {
				S = createPolinom(coeff, P->exp);
				insertEnd(head, S);
			}
			P = P->next;
		}
	}
}

void multPolinom(Position P, Position Q, Position head){
	Position S = NULL;
	Position temp = Q->next;
	P = P->next;
	Q = Q->next;
	int coeff = 1, exp = 0;

	while (P != NULL)
	{
		if (P == NULL)
			break;
		if (Q == NULL)
			break;
		while (Q != NULL) {
			coeff = P->coeff * Q->coeff;
			exp = P->exp + Q->exp;
			if (coeff != 0) {
				Sort(coeff, exp, head);
			}
			Q = Q->next;
		}
		Q = temp;
		P = P->next;
	}
	sortMult(head);
}

void Sort(int coeff, int exp, Position head)
{
	Position K=NULL;

	while (head->next != NULL && head->next->exp < exp)
		head = head->next;

	K = createPolinom(coeff, exp);

	K->next = head->next;
	head->next = K;
}

void sortMult(Position head)
{
	Position P, temp;
	P = head->next;
	while (P->next != NULL)
	{
		if (P->exp == P->next->exp)
		{
			P->coeff = P->coeff + P->next->coeff;
			temp = P->next;
			P->next = temp->next;
			free(temp);
		}
		else
			P = P->next;
	}
	P = head->next;
	while (P->next != NULL)
	{
		if (P->next->coeff == 0)
		{
			temp = P->next;
			P->next = temp->next;
			free(temp);
		}
		else
			P = P->next;
	}
}

void printList(Position head) {

	if (head->next == NULL)
		printf("Linked list is empty");
	
	head = head->next;
	while (head != NULL) {
		printf("\t%d\t%d\n", head->coeff, head->exp);
		head = head->next;
	}

	puts("\n");
}