#include "avltree.h"

avltree_node *avltree_node_new(int key)
{
	avltree_node *n = (avltree_node *)malloc(sizeof(avltree_node));

	n->key = key;
	n->avltree_height = 1;
	n->left = n->right = 0;

	return n;
}

unsigned char avltree_height(avltree_node* p)
{
	return (p) ? (p->avltree_height) : (0);
}

int avltree_balance_factor(avltree_node* p)
{
	return avltree_height(p->right) - avltree_height(p->left);
}

void avltree_height_fix(avltree_node* p)
{
	unsigned char hl = avltree_height(p->left);
	unsigned char hr = avltree_height(p->right);
	p->avltree_height = ((hl > hr) ? (hl) : (hr)) + 1;
}

avltree_node* avltree_rotateright(avltree_node* p)
{
	avltree_node* q = p->left;
	p->left = q->right;
	q->right = p;
	avltree_height_fix(p);
	avltree_height_fix(q);

	return q;
}

avltree_node* avltree_rotateleft(avltree_node* q) 
{
	avltree_node* p = q->right;
	q->right = p->left;
	p->left = q;
	avltree_height_fix(q);
	avltree_height_fix(p);

	return p;
}

avltree_node* avltree_balance(avltree_node* p) 
{
	avltree_height_fix(p);

	if (avltree_balance_factor(p) == 2)
	{
		if (avltree_balance_factor(p->right) < 0)
			p->right = avltree_rotateright(p->right);

		return avltree_rotateleft(p);
	}

	if (avltree_balance_factor(p) == -2)
	{
		if (avltree_balance_factor(p->left) > 0)
			p->left = avltree_rotateleft(p->left);

		return avltree_rotateright(p);
	}

	return p;
}

avltree_node* avltree_insert(avltree_node* p, int k)
{
	if (!p)
		return avltree_node_new(k);

	if (k<p->key)
		p->left = avltree_insert(p->left, k);
	else
		p->right = avltree_insert(p->right, k);

	return avltree_balance(p);
}

void avltree_free(avltree_node* tree)
{
	if (tree == NULL)
		return;

	avltree_free(tree->left);
	avltree_free(tree->right);

	free(tree);
}
