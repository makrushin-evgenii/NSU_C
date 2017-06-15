// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#include <stdio.h>

#include "linked_list.h"


void man_kill(Node **man)
{
	(*man)->data = 0; // 0 - убит, иначе - номер
}

Node *man_next(Node **list, Node *curent, int step)
{
	while (step - 1 || !curent->data)
	{
		if (curent->data)
			--step;

		if (curent->next)
			curent = curent->next;
		else if (!curent->next)
			curent = *list;
	}

	return curent;
}

Node *man_last_survived(Node *list)
{
	while (!list->data)
		list = list->next;

	return list;
}


int main()
{
	Node *people = NULL;

	int n = 4;
	int k = 2;

	for(int i = 0; i < n; ++i)
		list_push(&people, node_new(n - i));

	Node *curent = people;	// Очередь на растрел

	while (--n)
	{ 
		curent = man_next(&people, curent, k);
		man_kill(&curent);
	}

	Node *last_survived = man_last_survived(people);

	printf("%d", last_survived->data);

	return 0;
}
