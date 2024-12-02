#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _stog* position;
typedef struct _stog {
	int el;
	position next;
}stog;

int push(position p, double value);
double pop(position p);
int dat(FILE *fp,position p);
int handleop(position p,char operator);
void finalprint(position p);

int main() {

	stog Head;
	Head.next = NULL;

	FILE* fp = fopen("POSTFIX.txt", "r");
	if (fp == NULL) {
		printf("Greska 1");
		return 1;
	}

	if (dat(fp, &Head) != 0) {
		printf("GRESKA");
		fclose(fp);
		return 1;
	}

	fclose(fp);

	if (Head.next != NULL) {
		finalprint(&Head);
		printf("Rezultat: %.2f\n", Head.next->el);
	}
	else
		printf("GRESKA!");

	return 0;
}

int dat(FILE *fp, position p) {
	char buffer[100];

	while (fscanf(fp, "%s", buffer) != EOF) {
		printf("Reading token: %s\n", buffer);

		if(buffer[0] >= '0' && buffer[0] <= '9' || (buffer[0] == '-' && buffer[1] >= '0' && buffer[1] <= '9')) {
			double vrijednost = atof(buffer);
			printf("Pushing numbers: %.2f\n", vrijednost);
			push(p, vrijednost);
		}
		else if (strlen(buffer) == 1) {
			char oper = buffer[0];
			if (handleop(p, oper) != 0) {
				printf("Greska 2");
				return 1;
			}
		}
		else {
			printf("Greska 3");
			return 1;
		}
	}
	return 0;
}

int push(position p, double value) {
	position q = (position)malloc(sizeof(stog));
	if (q == NULL) {
		printf("Greska 4");
		return 1;
	}

	q->el = value;
	q->next = p->next;
	p->next = q;

	return 0;
}

double pop(position p) {
	if (p->next == NULL) {
		printf("Greska 5");
		return 0;
	}

	position temp = p->next;
	double value = temp->el;

	p->next = temp->next;
	free(temp);
	return value;
}

int handleop(position p, char operator) {

	if (p->next == NULL || p->next->next == NULL) {
		printf("Greska 6");
		return 1;
	}

	double first = pop(p);
	double second = pop(p);
	double result;

	switch (operator) {
		case'+':
			result = second + first;
			break;
		case'-':
			result = second - first;
			break;
		case'*':
			result = second * first;
			break;
		case'/':
			if (first == 0) {
				printf("Greska 7");
				return 1;
			}
			result = second / first;
			break;
		default:
			printf("Greska 8");
			return 1;
	}

	printf("Pushing result: %.2f\n", result);
	push(p, result);

	return 0;
}

void finalprint(position p) {
	position current = p->next;
	printf("Stack content: ");
	while (current != NULL) {
		printf("%.2f", current->el);
		current = current->next;
	}
	printf("\n");
}