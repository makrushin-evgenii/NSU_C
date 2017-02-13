#pragma once

#include <stdlib.h>


typedef struct Node
{
	int data;
	Node *next;
} Node;

/* создать узел с данными */
Node* node_new(int data);

/* получить адрес n-го узла */
Node* list_get_nth(Node* head, int n);

/* получить адрес последнего узла */
Node* list_get_last(Node* head);

/* добавить узел в начало списка*/
void list_push(Node **head, Node *node);

/* добавить узел в конец списка */
void list_push_back(Node **head, Node *node);

/* удалить узел из начала списка */
int list_pop(Node **head);

/* удалить узел из конца списка */
int list_pop_back(Node **head);

/* получить длину списка */
int list_length(Node *head);

/* очистить список */
void list_free(Node **head);
