#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _tree* treepointer;
typedef struct _tree {
	int data;
	treepointer left;
	treepointer right;
}tree;

tree* Create(int data) {
	tree* new = (tree*)malloc(sizeof(tree));
	new->data = data;
	new->left = new->right = NULL;
	return new;
}

tree* Insert(tree* root,int value) {
	if (root == NULL)
		return Create(value);
	
	if (value < root->data)
		root->left = Insert(root->left, value);
	else if (value > root->data)
		root->right = Insert(root->right, value);

	return root;
}

void Inorder(tree* root) {
	if (root != NULL) {
		Inorder(root->left);
		printf("%d ", root->data);
		Inorder(root->right);
	}
}

void Preorder(tree* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		Preorder(root->left);
		Preorder(root->right);
	}
}

void Postorder(tree* root) {
	if (root != NULL) {
		Postorder(root->left);
		Postorder(root->right);
		printf("%d ", root->data);
	}
}

void Printcurrentlevel(tree* root, int level) {
	if (root == NULL)
		return;
	if (level == 1)
		printf("%d ", root->data);
	else if (level > 1) {
		Printcurrentlevel(root->left, level - 1);
		Printcurrentlevel(root->right, level - 1);
	}
}

int Height(tree* root) {
	if (root == NULL)
		return 0;
	int LH = Height(root->left);
	int RH = Height(root->right);
	int max;
	if (LH > RH)
		max = LH;
	else
		max = RH;
	return max + 1;
}

void Level(tree* root) {
	int h = Height(root);
	for (int i = 0; i <= h; i++)
		Printcurrentlevel(root, i);
}

int Search(tree* root, int value) {
	if (root == NULL)	return 0;
	if (root->data == value)	return 1;
	if (value < root->data)	return Search(root->left, value);
	return Search(root->right, value);
}

tree* Min(tree* root) {
	while (root->left != NULL)
		root = root->left;
	return root;
}

tree* Del(tree* root, int value) {
	if (root == NULL)	return root;
	if (value < root->data)
		root->left = Del(root->left, value);
	else if (value > root->data)
		root->right = Del(root->right, value);
	else {
		if (root->left == NULL) {
			tree* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			tree* temp = root->left;
			free(root);
			return temp;
		}
		tree* temp = Min(root->right);
		root->data = temp->data;
		root->right = Del(root->right, temp->data);
	}
	return root;
}


int main() {

	tree* root = NULL;

	int numbers[] = { 5,3,2,4,7,6,8 };
	int n = sizeof(numbers) / sizeof(numbers[0]);
	for (int i = 0; i < n; i++)
		root = Insert(root, numbers[i]);
	int choice, value;

	do {
		printf("\n1. Dodaj element\n");
		printf("2. Ispis (inorder)\n");
		printf("3. Ispis (preorder)\n");
		printf("4. Ispis (postorder)\n");
		printf("5. Ispis (level order)\n");
		printf("6. Pronadi element\n");
		printf("7. Izbrisi element\n");
		printf("8. Izlaz\n");
		printf("Unesi izbor: ");	scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Unesi vrijednost: ");
				scanf("%d", &value);
				root = Insert(root, value);
				break;
			case 2:
				Inorder(root);
				printf("\n");
				break;
			case 3:
				Preorder(root);
				printf("\n");
				break;
			case 4:
				Postorder(root);
				printf("\n");
				break;
			case 5:
				Level(root);
				printf("\n");
				break;
			case 6:
				printf("Unesi vrijednost za pretragu: ");	scanf("%d", &value);
				if (Search(root, value))
					printf("Element pronaden.\n");
				else
					printf("Element ne postoji.\n");
				break;
			case 7:
				printf("Unesi vrijednost za brisanje: ");	scanf("%d", &value);
				root = Del(root, value);
				break;
			case 8:
				printf("Izlaz\n");
				break;
			default:
				printf("KRIVO\n");
		}
	} while (choice != 8);

	return 0;
}