#define _CRT_SECURE_NO_WARNINGS

#define CHAR_COUNT 256

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>

#include "pqueue.h"	// Generic priority queue (heap) used by the Apache HTTP Server project. 

typedef struct node_t
{
	pqueue_pri_t pri;
	char val;
	size_t pos;
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
	node_t   *n;

	ns = (node_t*)malloc(CHAR_COUNT * sizeof(node_t));
	pq = pqueue_init(CHAR_COUNT, cmp_pri, get_pri, set_pri, get_pos, set_pos);
	if (!(ns && pq)) return 1;


	// сортировка символов по убыванию
	for (size_t i = 0; i < CHAR_COUNT; ++i)
	{
		ns[i].pri = 0;
		ns[i].val = i;
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


	while ((n = pqueue_pop(pq)))
		printf("pop: %c [%lld]\n", n->val, n->pri);


	pqueue_free(pq);
	free(ns);

	return 0;
}
