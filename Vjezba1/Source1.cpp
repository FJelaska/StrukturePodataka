#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024

typedef struct {
	char ime[50];
	char prezime[50];
	double bodovi;
}Student;

int upis(FILE *fp, Student *s, int n);

int main() {

	int br = 0;
	FILE* fp = NULL;

	fp = fopen("studenti1.txt", "r");
	if (fp == NULL) {
		printf("Greska 1");
		return 1;
	}

	while (!feof(fp)) {
		if (fgetc(fp) == '\n')
			br++;
	}

	Student* s = NULL;
	s = (Student*)malloc(br * sizeof(Student));
	if (s == NULL)
		printf("Greska 2");

	rewind(fp);
	upis(fp, s, br);
	fclose(fp);

	return 0;
}

int upis(FILE* fp, Student* s, int n) {

	int i, max = 50;
	double rel;

	for (i = 0; i < n; i++) {
		if (fscanf(fp, "%s %s %lf\n", (*(s + i)).ime, (*(s + i)).prezime, &(*(s + i)).bodovi) == 3) {
			rel = s[i].bodovi / max * 100;
			printf("Ime i prezime: %s %s\t Bodovi: %.2lf\t Rel. bodovi: %.2lf\n", (*(s + i)).ime, (*(s + i)).prezime, (*(s + i)).bodovi, rel);
		}
		else
			printf("Greska 3");
	}
	return 0;
}