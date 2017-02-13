#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	node* left;
	node* right;
};

node *node_new(int key)
{
	node *n = (node *)malloc(sizeof(node));

	n->key = key;
	n->height = 1;
	n->left = n->right = 0;

	return n;
}

unsigned char height(node* p)
{
	return (p) ? (p->height) : (0);
}

int balance_factor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);

	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);

	return p;
}

node* balance(node* p) // балансировка узла p
{
	fixheight(p);

	if (balance_factor(p) == 2)
	{
		if (balance_factor(p->right) < 0)
			p->right = rotateright(p->right);

		return rotateleft(p);
	}
	if (balance_factor(p) == -2)
	{
		if (balance_factor(p->left) > 0)
			p->left = rotateleft(p->left);

		return rotateright(p);
	}

	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p)
		return node_new(k);

	if (k<p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);

	return balance(p);
}

void avltree_free(node* tree)
{
	if (tree == NULL)
		return;

	avltree_free(tree->left);
	avltree_free(tree->right);

	free(tree);
}



int main()
{
	struct node *tree = NULL;

	int n = 0;
	int cur = 0;

	scanf("%d", &n);

	while (n--)
	{
		scanf("%d", &cur);
		tree = insert(tree, cur);
	}

	printf("%d\n", height(tree));

	free(tree);

	return 0;
}
