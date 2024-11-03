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
int Crafter(position p);
int Crbefore(position p);
int SortPrez(position p);
int CreateDat(position p);
int ReadDat();

int main() {

	osoba Head;
	Head.next = NULL;
	char option;

	while (1) {
		printf("\nOdaberi zeljenu komandu:\n");
		printf("P - unos na pocetak\tI - ispis\nK - unos na kraj\tT - potrazi po prez\nX - izbrisi clana \tA - Dodaj iza\nB - dodaj ispred\tS - sort po prez\nD - dodaj u dat \tR - citaj dat\n");
		scanf(" %c", &option);

		if (option == 'p' || option == 'P')
			InStart(&Head);
		else if (option == 'i' || option == 'I')
			Print(Head.next);
		else if (option == 'k' || option == 'K')
			InEnd(&Head);
		else if (option == 't' || option == 'T')
			FindP(Head.next);
		else if (option == 'x' || option == 'X')
			Del(&Head);
		else if (option == 'a' || option == 'A')
			Crafter(&Head);
		else if (option == 'b' || option == 'B')
			Crbefore(&Head);
		else if (option == 's' || option == 'S')
			SortPrez(&Head);
		else if (option == 'd' || option == 'D')
			CreateDat(Head.next);
		else if (option == 'r' || option == 'R')
			ReadDat();
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

int Crafter(position p) {

	position novi = NULL;
	novi = (position)malloc(sizeof(osoba));

	if (novi == NULL) {
		printf("Greska 7");
		return 1;
	}

	printf("\nUnesi ime: ");	scanf("%s", novi->ime);
	printf("Unesi prezime: ");	scanf("%s", novi->prez);
	printf("Unesi god rod: "); scanf("%d", &novi->god);
	puts("");

	char prezim[50];

	printf("\nUnesi prezime iza kojeg zelis unos nove osobe: "); scanf(" %s", prezim);

	while (p->next != NULL && strcmp(prezim, p->prez) != 0)
		p = p->next;

	novi->next = p->next;
	p->next = novi;
	
	return 0;
}

int Crbefore(position p) {

	position prev = NULL;
	position novi = NULL;
	char prezim[50];

	novi = (position)malloc(sizeof(osoba));

	if (novi == NULL) {
		printf("Greska 8");
		return 1;
	}

	printf("\nUnesi ime: ");	scanf("%s", novi->ime);
	printf("Unesi prezime: ");	scanf("%s", novi->prez);
	printf("Unesi god rod: "); scanf("%d", &novi->god);
	puts("");


	printf("\nUnesi prezime iza kojeg zelis unos nove osobe: "); scanf(" %s", prezim);

	prev = p;
	while (p->next != NULL && strcmp(prezim, p->prez) != 0) {
		prev = p;
		p = p->next;
	}

	if (p->next != NULL) {
		novi->next = p;
		prev->next = novi;
	}

	return 0;
}

int SortPrez(position p) {

	position q = NULL;
	position prev_q = NULL;
	position temp = NULL;
	position end = NULL;

	while (p->next != end) {
		prev_q = p;
		q = p->next;

		while (q->next != end) {
			if (strcmp(q->prez, q->next->prez) > 0) {
				temp = q->next;
				prev_q->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}
			prev_q = q;
			q = q->next;
		}
		end = q;
	}

	Print(p->next);

	return 0;
}

int CreateDat(position p) {

	FILE* dat = NULL;

	dat = fopen("osobe.txt", "w");
	if (dat == NULL) {
		printf("Greska 9");
		return 1;
	}

	while (p != NULL) {
		fprintf(dat, "%s\t%s\t%d\t\n", p->ime, p->prez, p->god);
		p = p->next;
	}

	fclose(dat);
	return 0;
}

int ReadDat() {

	char dat[50];
	int i,br = 0;
	osoba Head;
	Head.next = NULL;
	position p = &Head;
	position q = NULL;

	printf("\nUnesi ime dat koju zelis otvorit: "); scanf(" %s", &dat);

	FILE* fp = NULL;
	fp = fopen(dat, "r");

	if (fp == NULL) {
		printf("Greska 10");
		return 1;
	}

	while (!feof(fp)) {
		if (fgetc(fp) == '\n')
			br++;
	}
	rewind(fp);

	if (br != 0) {
		for (i = 0; i < br; i++) {
			q = (position)malloc(sizeof(osoba));
			if (q == NULL) {
				printf("Greska 10");
				return 1;
			}

			fscanf(fp, "%s %s %d", q->ime, q->prez, &q->god);
			q->next = p->next;
			p->next = q;
			p = p->next;
		}
	}

	fclose(fp);
	Print(Head.next);

	return 0;
}