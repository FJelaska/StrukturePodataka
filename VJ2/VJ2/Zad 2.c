#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _osoba;
typedef struct _osoba* position;

typedef struct _osoba {
	char ime[50];
	char prez[50];
	int god;

	position next;
}osoba;

int In(position p);
int InStart(position p);
int Print(position p);
int InEnd(position p);
int FindP(position p);
int Del(position p);

int main() {

	osoba Head;
	Head.next = NULL;
	char option;

	while (1) {
		printf("\nOdaberi zeljenu komandu:\n");
		printf("P - unos na pocetak\tI - ispis\tK - unos na kraj\tT - potrazi po prez\tB - izbrisi\n");
		scanf(" %c", &option);
		
		if (option == 'p' || option == 'P')
			InStart(&Head);
		else if (option == 'i' || option == 'I')
			Print(Head.next);
		else if (option == 'k' || option == 'K')
			InEnd(&Head);
		else if (option == 't' || option == 'T')
			FindP(Head.next);
		else if (option == 'b' || option == 'B')
			Del(&Head);
		else {
			printf("\nKrivi unos");
			break;
		}
	}

	return 0;
}


int In(position p) {

	position r = NULL;
	r = (position)malloc(sizeof(osoba));

	if (r == NULL) {
		printf("Greska 1");
		return 1;
	}

	printf("\nUnesi ime: ");	scanf("%s", r->ime);
	printf("Unesi prezime: ");	scanf("%s", r->prez);
	printf("Unesi god rod: "); scanf("%d", &r->god);
	puts("");

	r->next = p->next;
	p->next = r;

	
	return 0;
}

int InStart(position p) {

	if (p == NULL) {
		printf("Greska 2");
		return 1;
	}

	In(p);

	return 0;
}

int Print(position p) {

	if (p == NULL) {
		printf("Greska 3");
		return 1;
	}
	puts("");

	while (p != NULL) {
		printf("%s %s %d\n", p->ime, p->prez, p->god);
		p = p->next;
	}
	
	return 0;
}

int InEnd(position p) {

	if (p == NULL) {
		printf("Greska 4");
		return 1;
	}

	while (p->next != NULL)
		p = p->next;

	In(p);

	return 0;
}

int FindP(position p) {

	char prez[50];

	printf("\nUnesi prezime trazene osobe: "); scanf(" %s", &prez);

	while (p != NULL && strcmp(prez, p->prez) != 0) {
		p = p->next;
	}
	if (p == NULL)
		printf("Greska 5");
	else
		printf("\nAdresa trazene osobe: %p\n", p);

	return 0;
}

int Del(position p) {

	position last = p;
	position temp = NULL;
	char prez[50];

	printf("\nUnesi prezime osobe koju zelis izbrisati: "); scanf(" %s", &prez);
	
	while (p->next != NULL && strcmp(prez, p->next->prez) != 0) {
		last = p;
		p = p->next;
	}

	if (p->next == NULL) {
		printf("Greska 6");
		return 1;
	}

	temp = p->next;
	p->next = temp->next;
	free(temp);
	
	return 0;
}