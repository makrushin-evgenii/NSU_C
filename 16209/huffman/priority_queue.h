#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
/* размер очереди */
#define SIZE_PRIORITY_QUEUE 128

/* TODO: fix dohuya definition*/
/* состояния очереди */
//const int ok_priority_queue = 0;
//const int full_priority_queue = 1;
//const int empty_priority_queue = 2;
/* переменная ошибок */
//extern int error_priority_queue;

/* базовый тип */
typedef struct {
	int data;
	int priority;
} priority_queue_base_type;

/* дескриптор */
typedef struct {
	priority_queue_base_type buf[SIZE_PRIORITY_QUEUE];
	unsigned head; /* указатель на хвост */
} priority_queue;

/* функции работы с очередью */

/**
*Summary.
*
*\param x: ... .
*\param y: ... .
*/
void init_priority_queue(priority_queue *F);
void put_priority_queue(priority_queue *F, priority_queue_base_type E);
void get_priority_queue(priority_queue *F, priority_queue_base_type *E);
//int is_full_priority_queue(priority_queue *F);
//int is_empty_priority_queue(priority_queue *F);

#endif
