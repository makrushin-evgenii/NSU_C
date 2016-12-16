#include "priority_queue.h"

/* TODO: fix dohuya definition*/
/* переменная ошибок */
//int error_priority_queue;

/* инициализация очереди */
void init_priority_queue(priority_queue *F)
{
	F->head = 0;
	//error_priority_queue = ok_priority_queue;
}

void put_priority_queue(priority_queue *F, priority_queue_base_type E)
{
	/*if (is_full_priority_queue(F))
		return;*/

	F->buf[F->head] = E;
	F->head++;
}

void get_priority_queue(priority_queue *F, priority_queue_base_type *E)
{
	/*if (is_empty_priority_queue(F))
		return;*/
	
	priority_queue_base_type max = F->buf[0];
	unsigned max_pos = 0;
	for (unsigned i = 0; i < F->head; ++i)
	{
		if (F->buf[i].priority > max.priority)
		{
			max = F->buf[i];
			max_pos = i;
		}
		*E = max;
		F->buf[max_pos] = F->buf[F->head - 1];
		F->head--;
	}

}

//int is_full_priority_queue(priority_queue *F)
//{
//	if (F->head == SIZE_PRIORITY_QUEUE)
//	{
//		error_priority_queue = full_priority_queue;
//		return 1;
//	}
//
//	return 0;
//}
//
//int is_empty_priority_queue(priority_queue *F)
//{
//	if (F->head == 0)
//	{
//		error_priority_queue = empty_priority_queue;
//		return 1;
//	}
//
//	return 0;
//}
