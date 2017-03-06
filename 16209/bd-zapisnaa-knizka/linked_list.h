#pragma once

#include <stdlib.h>


typedef struct Node
{
	void *data;
	struct Node *next;
} Node;

/* создать узел с данными */
Node* node_new(void *data);

/* получить адрес n-го узла */
Node* list_get_nth(Node* head, int n);

/* получить адрес последнего узла */
Node* list_get_last(Node* head);

/* добавить узел в начало списка*/
void list_push(Node **head, Node *node);

/* добавить узел в конец списка */
void list_push_back(Node **head, Node *node);

/* удалить узел из начала списка */
void *list_pop(Node **head);

/* удалить узел из конца списка */
void *list_pop_back(Node **head);

/* Удалить по номеру */
void *list_pop_nth(Node **head, int n);

/* получить длину списка */
int list_length(Node *head);

/* применяет функцию func к каждому элементу списка */
void list_foreach(Node *head, void(func)(Node*));

/* возвращает тот узел, для которого результат функции сравнения равен нулю */
Node* list_find(Node *head, int (cmp_func)(Node *cur, void *), void *pattern);

/* очистить список */
void list_free(Node **head);
