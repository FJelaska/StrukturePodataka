#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node {
	int value;
	struct Node *left, *right;
} Node;

Node* createNode(int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

Node* Insert(Node* root, int value) {
	if (root == NULL)
		return createNode(value);

	if (value <= root->value)
		root->left = Insert(root->left, value);
	else 
		root->right = Insert(root->right, value);
	
	return root;
}

int Replace(Node* root) {
	if (root == NULL)
		return 0;

	int LSum = Replace(root->left);
	int RSum = Replace(root->right);
	int oldValue = root->value;

	root->value = LSum + RSum;
	return oldValue + root->value;
}

void InOrder(Node* root, FILE* file) {
	if (root == NULL)
		return 0;

	InOrder(root->left, file);
	fprintf(file, "%d ", root->value);
	InOrder(root->right, file);
}

int main() {

	int stablo[] = { 2,5,7,8,11,1,4,2,3,7 };
	int i, n = sizeof(stablo) / sizeof(stablo[0]);
	FILE* file;

	Node* root = NULL;
	for (i = 0; i < n; i++)
		root = Insert(root, stablo[i]);

	//pod a)
	file = fopen("InOrder_a.txt", "w");
	if (!file) {
		printf("Greska 1");
		return 1;
	}
	InOrder(root, file);
	fclose(file);

	//pod b)
	Replace(root);
	file = fopen("InOrder_b.txt", "w");
	if (!file) {
		printf("Greska 2");
		return 1;
	}
	InOrder(root, file);
	fclose(file);

	//pod c)
	srand(time);
	Node* randomRoot = NULL;
	for (i = 0; i < n; i++) {
		int randomVal = 10 + rand() % 81;
		randomRoot = Insert(randomRoot, randomVal);
	}

	file = fopen("InOrder_c.txt", "w");
	if (!file) {
		printf("Greska 3");
		return 1;
	}
	InOrder(randomRoot, file);
	fclose(file);

	return 0;
}