/* размер очереди */
#define SIZE_PRIORITY_QUEUE 128

/* состояния очереди */
#define PQ_OK 0
#define PQ_FULL 0
#define PQ_EMPTY 0

/* переменная ошибок */
extern int pq_error;

/* базовый тип */
typedef struct {
	char data;
	int priority;
} pq_base_type;

/* дескриптор */
typedef struct {
	pq_base_type buf[SIZE_PRIORITY_QUEUE];
	unsigned head; /* указатель на хвост */
} priority_queue;

/* функции работы с очередью */

/**
*Инициализурет новую очередь по указателю F.
*\param *F: указатель на новую очередь.
*/
void pq_init(priority_queue *F);

/**
*Добавляет эл-т E в очередь F
*\param *F: указатель на очередь.
*\param E: добавляемый эл-т.
*/
void pq_insert(priority_queue *F, pq_base_type E);

/**
*Записывает эл-т с минимальным значением ключа в переменную E, удаляя его из F.
*\param *F: указатель на очередь.
*\param  E: переменная, куда будет записан эл-т.
*/
void pq_extract_minimum(priority_queue *F, pq_base_type *E);

int pq_is_full(priority_queue *F);
int pq_is_empty(priority_queue *F);
