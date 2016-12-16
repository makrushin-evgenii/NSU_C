#include "priority_queue.h"

int pq_error;

void pq_init(priority_queue *F)
{
	F->head = 0;
	pq_error = PQ_OK;
}

void pq_insert(priority_queue *F, pq_base_type E)
{
	if (pq_is_full(F))
		return;

	F->buf[F->head] = E;
	F->head++;
}

void pq_extract_minimum(priority_queue *F, pq_base_type *E)
{
	if (pq_is_empty(F))
		return;
	
	pq_base_type min = F->buf[0];
	unsigned max_pos = 0;
	for (unsigned i = 0; i < F->head; ++i)
	{
		if (F->buf[i].priority < min.priority)
		{
			min = F->buf[i];
			max_pos = i;
		}
	}

	*E = min;
	F->buf[max_pos] = F->buf[F->head - 1];
	F->head--;
}

int pq_is_full(priority_queue *F)
{
	if (F->head == SIZE_PRIORITY_QUEUE)
	{
		pq_error = PQ_FULL;
		return 1;
	}

	return 0;
}

int pq_is_empty(priority_queue *F)
{
	if (F->head == 0)
	{
		pq_error = PQ_EMPTY;
		return 1;
	}

	return 0;
}
