#define _CRT_SECURE_NO_WARNINGS

#define CHAR_COUNT 256

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>

#include "pqueue.h"	// github.com/vy/libpqueue 

typedef struct node_t
{
	pqueue_pri_t pri;
	char val;
	size_t pos;

	struct node_t *left;
	struct node_t *right;
} node_t;


static int
cmp_pri(pqueue_pri_t next, pqueue_pri_t curr)
{
	return (next > curr);
}


static pqueue_pri_t
get_pri(void *a)
{
	return ((node_t *)a)->pri;
}


static void
set_pri(void *a, pqueue_pri_t pri)
{
	((node_t *)a)->pri = pri;
}


static size_t
get_pos(void *a)
{
	return ((node_t *)a)->pos;
}


static void
set_pos(void *a, size_t pos)
{
	((node_t *)a)->pos = pos;
}


int main(int argc, int * argv[])
{
	
	FILE *fin = stdin;	// по умолчанимаю ввод через stdin
	FILE *fout = stdout;	// по умолчанимаю вывод через stdout

	fin = fopen("in.txt", "r");	// для отладки

	_setmode(_fileno(fin), _O_BINARY);
	_setmode(_fileno(fout), _O_BINARY);

	char buff[1024] = { 0 };					// читать будем блоками по киловайту
	const size_t buff_size = sizeof(buff) / sizeof(*buff);		// но  это не точно
	size_t cur_size = 0;						// сколько смогли прочитать


	pqueue_t *pq;
	node_t   *ns;
	

	ns = (node_t*)malloc(CHAR_COUNT * sizeof(node_t));
	pq = pqueue_init(CHAR_COUNT, cmp_pri, get_pri, set_pri, get_pos, set_pos);
	if (!(ns && pq)) return 1;


	// Сортировка символов по убыванию
	for (size_t i = 0; i < CHAR_COUNT; ++i)
	{
		ns[i].val = i;
		ns[i].pri = 0;
		ns[i].right = ns[i].left = NULL;
	}
	while (cur_size = fread(buff, 1, buff_size, fin))
	{
		for (size_t i = 0; i < cur_size; ++i)
		{
			char c = buff[i];
			++ns[c].pri;
		}
	}
	for (size_t i = 0; i < CHAR_COUNT; ++i)
	{
		if (ns[i].pri != 0)
			pqueue_insert(pq, &ns[i]);
	}
	fseek(fin, 0, SEEK_SET);

	// Постройка дерева от листьев к корню
	while (pqueue_size(pq) > 1)
	{
		node_t   *l = pqueue_pop(pq);
		node_t   *r = pqueue_pop(pq);

		node_t *merged_nodes = (node_t*)malloc(sizeof(node_t));
		merged_nodes->val = 0;
		merged_nodes->left = l;
		merged_nodes->right = r;
		merged_nodes->pri = l->pri + r->pri;

		pqueue_insert(pq, merged_nodes);

		// printf("pop: %c [%lld]; ", merged_nodes->val, merged_nodes->pri);
		// printf("pop: %c [%lld]; ", l->val, l->pri);
		// printf("pop: %c [%lld]\n", r->val, r->pri);
	}

	pqueue_free(pq);
	free(ns);

	return 0;
}
