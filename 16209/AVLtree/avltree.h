#pragma once

#include <stdlib.h>

typedef struct avltree_node
{
	int key;
	unsigned char avltree_height;	// высота (не balance factor!)
	struct avltree_node* left;		
	struct avltree_node* right;
} avltree_node;

/* конструктор по ключу */
avltree_node *avltree_node_new(int key);

/* возвращает высоту.
 * корректно обрабатывает нулевой указатель
 */
unsigned char avltree_height(avltree_node* p);

/* вычисляет balance factor
 * работает только с инициализироваными вершинами
 */
int avltree_balance_factor(avltree_node* p);

/* восстанавливает корректное значение поля height узла p 
 * при условии, что значения этого поля в правом и левом дочерних узлах являются корректными
 */
void avltree_height_fix(avltree_node* p);

avltree_node* avltree_rotateright(avltree_node* p);

avltree_node* avltree_rotateleft(avltree_node* q);

avltree_node* avltree_balance(avltree_node* p);

avltree_node* avltree_insert(avltree_node* p, int k);

void avltree_free(avltree_node* tree);
