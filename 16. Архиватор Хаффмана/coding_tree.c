// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <stdio.h>

#include "leaks_debug.h"
#include "coding_tree.h"
#include "pqueue.h"

#define ASCII_MAX_CHAR 256

//
//  Функции для инициализации libpqueue...
//

static int cmp_pri(pqueue_pri_t next, pqueue_pri_t curr)
{
	return (next > curr);
}

static pqueue_pri_t get_pri(void *a)
{
	return ((node_t *)a)->priority;
}

static void set_pri(void *a, pqueue_pri_t pri)
{
	((node_t *)a)->priority = pri;
}

static size_t get_pos(void *a)
{
	return ((node_t *)a)->pos;
}

static void set_pos(void *a, size_t pos)
{
	((node_t *)a)->pos = pos;
}

// ... конец инициализации libpqueue

//
// Новый элемент дерева.
//

// leaf - true если терминирующий узел, false если внутренний,
// chars_freq - частота вхождения символа. Можно не указывать для внутреннего узла,
// c - ASCII код символа,
// left, right - дочерние эл-ты.
node_t * tree_new_node(bool leaf, size_t chars_freq, uint8_t c, node_t * left, node_t * right)
{
	node_t * node = (node_t *)malloc(sizeof(node_t));
	node->value = c;
	node->left = left, node->right = right;
	node->is_leaf = leaf;

	if (leaf)
		node->priority = chars_freq;
	else
		node->priority = (left ? left->priority : 0) + (right ? right->priority : 0);

	return node;
}

node_t* tree_new_internal(node_t* left, node_t* right)
{
	return tree_new_node(false, 0, 0, left, right);
}

node_t* tree_new_leaf(size_t priority, uint8_t value)
{
	return tree_new_node(true, priority, value, NULL, NULL);
}

void tree_free(node_t* tree)
{
	if (!tree)
		return;

	tree_free(tree->left);
	tree_free(tree->right);
	free(tree);
}

node_t* tree_build_with_freqs(size_t chars_freq[])
{
	pqueue_t * pq = pqueue_init(ASCII_MAX_CHAR, cmp_pri, get_pri, set_pri, get_pos, set_pos);

	// создаем узлы бинарного дерева для каждого знака и добавим их в очередь, используя частоту в качестве приоритета
	for (size_t i = 0; i < ASCII_MAX_CHAR; ++i)
		if (chars_freq[i])
			pqueue_insert(pq, tree_new_leaf(chars_freq[i], (uint8_t)i));

	// продолжаем обьедиинять узлы, пока не останется только корень дерева
	// при этом два первых элемента из очереди образуют новый узел дерева,
	// в котором они оба будут потомками, а приоритет нового узла будет равен сумме их приоритетов
	if (pqueue_size(pq) == 1)		// если в файле встречается только один символ
	{					// для надежности суем его в обе стороны
		node_t* node = pqueue_pop(pq);
		pqueue_insert(pq, tree_new_internal(node, node));
	}
	else while (pqueue_size(pq) > 1)
		pqueue_insert(pq, tree_new_internal(pqueue_pop(pq), pqueue_pop(pq)));

	node_t* tree = (node_t*)pqueue_pop(pq);
	pqueue_free(pq);


	return tree;
}
