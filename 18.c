/*Задание 18. Сортировка вставкой в список*/ 
#include <stdio.h>
#include <stdlib.h>

struct item{
	int data;
	struct item *next;
};
struct item *head;

int main(void){

	struct item *q, *p;
	int a;

	while(scanf("%d", &a) == 1)
	{
		struct item *new_node;
		new_node = malloc(sizeof(struct item));
		new_node->data = a;
		new_node->next = NULL;

		// q - меньше или равен, p - больше элемента
		// если q == NULL, то это начало списка
		for(q = NULL, p = head; p && p->data < new_node->data; q = p, p = p->next)
			;
		if(q == NULL){
			new_node->next = head;
			head = new_node;

		}
		else{
			q->next = new_node;
			new_node->next = p;
		}
		
	}

	// выввод списка
	for(p = head; p; p = p->next)
		printf("%d ", p->data);
	putchar('\n');

	return 0;
}
