/*Задание 21. Сортировка вставкой в дерево.*/ 
#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *left, *right;
};
struct node *root;

void infix(struct node *root){
	if(root == NULL)
		return;
	infix(root->left);
	printf("%d ", root->data);
	infix(root->right);
}

struct node *free_node(int value){
	struct node *p;
	p = malloc(sizeof(struct node));
	p->data = value;
	return p;
}

void insert_node(struct node **root, int value){
	if(*root == NULL){
		*root = free_node(value);
		return;
	}

	if(value > (*root)->data)
		insert_node(&((*root)->right), value);
	else
		insert_node(&((*root)->left), value);
}


int main(void){

	int a;

	while(scanf("%d", &a) == 1)
		insert_node(&root, a);

	infix(root);

	return 0;
}
