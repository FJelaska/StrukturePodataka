#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024


int brRed(const char*);

int main() {

	int brred = 0;

	brred = brRed("imedat.txt");

	return 0;
}


int brRed(const char*fileName) {

	FILE*fp = NULL;
	int brRed = 0;
	char buffer[MAX] = {};

	fp = fopen(fileName, "r");
	if (!fp)
		return -1;

	while (!feof(fp)) {
		fgets(buffer, MAX, fp);
		brRed++;
	}

	fclose(fp);
	return 0;
}