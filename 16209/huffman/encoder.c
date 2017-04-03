#include "encoder.h"

#include <stdint.h>	// uint8_t, size_t etc
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>

#include "pqueue.h"


typedef struct node_t {
	pqueue_pri_t pri;
	uint8_t val;
	size_t pos;

	struct node_t * left;
	struct node_t * right;
} node_t;

//
//  Функции для инициализации libpqueue...
//

static int cmp_pri(pqueue_pri_t next, pqueue_pri_t curr)
{
	return (next > curr);
}

static pqueue_pri_t get_pri(void *a)
{
	return ((node_t *)a)->pri;
}

static void set_pri(void *a, pqueue_pri_t pri)
{
	((node_t *)a)->pri = pri;
}

static size_t get_pos(void *a)
{
	return ((node_t *)a)->pos;
}

static void set_pos(void *a, size_t pos)
{
	((node_t *)a)->pos = pos;
}

// ...инициализации libpqueue

node_t * new_node(size_t freq, uint8_t c, node_t * left, node_t * right)
{
	node_t * n = (node_t *)malloc(sizeof(node_t));
	n->val = c;
	n->left = left, n->right = right;
	if (freq)
		n->pri = freq;
	else
	{
		n->pri = left->pri + right->pri;
	}

	return n;
}

void fgetc_freq(char * file_name, size_t * freq)
{
	FILE * fin = fopen(file_name, "r");
	if (fin == NULL) { return; }
	_setmode(_fileno(fin), _O_BINARY);

	uint8_t buff[1024];										// читать будем блоками по киловайту
	size_t buff_size = sizeof(buff) / sizeof(*buff);		// но это не точно
	size_t cur_size = 0;									// сколько смогли прочитать

	
	while ((cur_size = fread(buff, 1, buff_size, fin)) > 0)
	{
		for (size_t i = 0; i < cur_size; ++i)
		{
			++freq[buff[i]];
		}
	}

	fclose(fin);
}

// обход дерева в глубину: 0 - left, 1 - right
// head - корень дерева
// s - строка, в которую накапливается код символа, len - смещение ввода
// code - здесь будут коды символов
void build_code(node_t * head, uint8_t * code[], uint8_t * s, int len)
{
	if (!head)
		return;

	if (head->val)
	{
		s[len] = 0;
		code[head->val] = malloc(sizeof(uint8_t) * len);
		strcpy(code[head->val], s);
		return;
	}

	s[len] = '0', build_code(head->left, code, s, len + 1);
	s[len] = '1', build_code(head->right, code, s, len + 1);
}

// скобочная запись дерева (для отладки)
void tree_print(node_t * root)
{
	if (!root)
	{
		putchar('x');
		return;
	}

	putchar('(');
	if (root->val)
		putchar(root->val);
	else
		putchar('N');
	tree_print(root->left);
	tree_print(root->right);
	putchar(')');
}

void encoding(char * input_file_name, char * output_file_name)
{
	//
	// TODO: вынести все это в отдельную ф-ию init()
	//

	// частота вхождения каждого символа
	size_t freq[256] = { 0 };
	fgetc_freq(input_file_name, freq);
	
	// построение кодирующего дерева
	pqueue_t * pq = pqueue_init(256, cmp_pri, get_pri, set_pri, get_pos, set_pos);
	for (size_t i = 0; i < 256; ++i)
	{
		if (freq[i])
		{
			pqueue_insert(pq, new_node(freq[i], (uint8_t)i, NULL, NULL));
		}
	}
	// обьедиинять узлы, пока в очереди больше одного
	while (pqueue_size(pq) >= 2)
	{
		pqueue_insert(pq, new_node(0, (uint8_t)0, (node_t *)pqueue_pop(pq), (node_t *)pqueue_pop(pq)));
	}
	
	// собраное дерево
	tree_print((node_t *)pqueue_peek(pq)); putchar('\n');

	uint8_t *code[256] = { 0 };
	uint8_t s[16];
	node_t * root = (node_t *)pqueue_peek(pq);
	build_code(root, code, s, 0);

}
