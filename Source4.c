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
void insertStart(Position, Position);
void printList(Position);

int main() {
	FILE* File;
	Position P = NULL;
	Position Q = NULL;
	polinom head1;
	polinom head2;
	head1.next = NULL;
	head2.next = NULL;
	int coeff = 0, exp = 0;
	char datName[256];
	printf("Insert file name: ");
	scanf("%s",datName);
	File = fopen(datName, "r");
	if (!File)
		printf("File failed to open!");

	int n=0,i;
	char* buffer = malloc(1024);
	while (1) {
		if (fgets(buffer, 50, File) == '\0')
			break;
		n++;
	}
	rewind(File);
	char c;
	while (!feof(File)) 
	{
		c = fgetc(File);
		if (c != '\n') {
			fscanf(File, "%d %d", &coeff, &exp);
			P = createPolinom(coeff, exp);
			insertStart(&head1, P);
		}else {
			while (!feof(File)) {
				fscanf(File, "%d %d", &coeff, &exp);
				Q = createPolinom(coeff, exp);
				insertStart(&head2, Q);
			}
		}
	}
	printList(&head1);
	printList(&head2);
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


void insertStart(Position head, Position K) {
	
	K->next = head->next;
	head->next = K;

}

void printList(Position head) {
	
	Position K = NULL;
	
	printf("\nlist content:\n");
	if (head->next == NULL)
		printf("Linked list is empty");
	
	K = head->next;
	while (K != NULL) {
		printf("\t%d %d\n", K->coeff, K->exp);
		K = K->next;
	}

	puts("\n");
}