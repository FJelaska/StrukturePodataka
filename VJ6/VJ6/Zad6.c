#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Artikl {
	char name[50];
	int quant;
	float price;
	struct _Artikl* next;
}Artikl;

typedef struct _Racun {
	char date[11];
	Artikl* artikli;
	struct _Racun* next;
}Racun;

Artikl* newArtikl(char* name, int quant, float price);
void InAritkl(Artikl** head, char* name, int quant, float price);

Racun* newRacun(char* date);
void InRacun(Racun** head, char* date, char* name, int quant, float price);
void TotalExpenses(Racun* head, char* artname, char* dateOd, char* dateDO);

void dat(Racun** racuni, const char* imegldat);
int Compare(char* date1, char* date2);

int main() {

	Racun* racuni = NULL;
	char art[50], datOD[11], datDO[11];

	dat(&racuni, "racuni.txt");

	printf("Unesi artikl: ");	scanf("%s", art);
	printf("Unesi pocetni datum gledanja (YYYY-MM-DD): ");	scanf("%s", datOD);
	printf("Unesi krajnji datum gledanja (YYYY-MM-DD): ");	scanf("%s", datDO);

	TotalExpenses(racuni, art, datOD, datDO);

	return 0;
}

//novi artikl
Artikl* newArtikl(char* name, int quant, float price) {
	Artikl* newA = (Artikl*)malloc(sizeof(Artikl));
	if (!newA) {
		printf("Greska 1");
		return NULL;
	}
	strcpy(newA->name, name);
	newA->quant = quant;
	newA->price = price;
	newA->next = NULL;
	return newA;
}

//dodaje novi artikl u sort listu
void InAritkl(Artikl** head, char* name, int quant, float price) {
	Artikl* new = newArtikl(name, quant, price);
	if (!new)	return;

	Artikl* current = *head;
	Artikl* prev = NULL;

	while (current != NULL && strcmp(current->name, name) < 0) {
		prev = current;
		current = current->next;
	}

	if (current != NULL && strcmp(current->name, name) == 0) {
		current->quant += quant;
		free(new);
	}
	else {
		if (prev == NULL) {
			new->next = *head;
			*head = new;
		}
		else {
			prev->next = new;
			new->next = current;
		}
	}
}

//novi racun
Racun* newRacun(char* date) {
	Racun* newR = (Racun*)malloc(sizeof(Racun));
	if (!newR) {
		printf("Greska 2");
		return NULL;
	}
	strcpy(newR->date, date);
	newR->artikli = NULL;
	newR->next = NULL;
	return newR;
}

//dodaje novi racun u sort listu
void InRacun(Racun** head, char* date, char* name, int quant, float price) {
	Racun* current = *head;
	Racun* prev = NULL;

	while (current != NULL && strcmp(current->date, date) < 0) {
		prev = current;
		current = current->next;
	}

	if (current != NULL && strcmp(current->date, date) == 0) {
		InAritkl(&(current->artikli),name,quant,price);
	}
	else {
		Racun* new = newRacun(date);
		if (!new)	return;
		InAritkl(&(new->artikli), name, quant, price);
		if (prev == NULL) {
			new->next = *head;
			*head = new;
		}
		else {
			prev->next = new;
			new->next = current;
		}
	}
}

void TotalExpenses(Racun* head, char* artname, char* dateOD, char* dateDO) {
	int ukkol = 0;
	float ukcj = 0.0;

	while (head != NULL) {
		if (Compare(head->date, dateOD) >= 0 && Compare(head->date, dateDO) <= 0) {
			Artikl* artikli = head->artikli;
			while (artikli != NULL) {
				//printf("Provjera: %s, datum: %s, kol: %d, cj: %.2f\n", artikli->name, head->date, artikli->quant, artikli->price);
				if (strcmp(artikli->name, artname) == 0) {
					ukkol += artikli->quant;
					ukcj += artikli->price * artikli->quant;
				}
				artikli = artikli->next;
			}
		}
		head = head->next;
	}

	printf("Ukupno potroseno na '%s' u tom vremenskom periodu je: %.2f\n", artname, ukcj);
	printf("Ukupna kolicina proizvoda: %d\n", ukkol);
}

void dat(Racun** racuni, const char* imegldat) {
	FILE* fp = fopen(imegldat, "r");
	if (!fp) {
		printf("Greska 3");
		return;
	}

	char ime[50];
	while (fscanf(fp, "%s", ime) == 1) {
		printf("Ucitana datoteka: %s\n", ime);
		FILE* racun = fopen(ime, "r");
		if (!racun) {
			printf("Greska 4");
			continue;
		}

		char datum[11];
		if (fscanf(racun, "%10s", datum) != 1) {
			printf("Greska 5");
			fclose(racun);
			continue;
		}
		
		char name[50];
		int kol;
		float cj;

		while (fscanf(racun, "%49[^,],%d,%f\n", name, &kol, &cj) == 3) {
			//printf("Unos: %s, kol: %d, cj: %.2f\n", name, kol, cj);
			InRacun(racuni, datum, name, kol, cj);
		}
	
		fclose(racun);
	}
	fclose(fp);
}

int Compare(char* date1, char* date2) {
	int y1, m1, d1;
	int y2, m2, d2;

	sscanf(date1, "%d-%d-%d", &y1, &m1, &d1);
	sscanf(date2, "%d-%d-%d", &y2, &m2, &d2);

	if (y1 < y2)	return -1;
	if (y1 > y2)	return 1;

	if (m1 < m2)	return -1;
	if (m1 > m2)	return 1;

	if (d1 < d2)	return -1;
	if (d1 > d2)	return 1;

	return 0;
}
