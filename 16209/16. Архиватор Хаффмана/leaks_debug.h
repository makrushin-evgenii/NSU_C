/** Режим отладки Heap-а.
 * 0 - Нет отладки.
 * 1 - Следить за созданием и удалением объектов.
 * 2 - Следить за созданием и удалением объектов и выводить в stdout позиции вызова malloc и free. */
#define DEBUG_HEAP 1

#include <stdlib.h>

#if DEBUG_HEAP > 0

 /** Функция перехватывающая стандартный malloc для слежки за выделенными объектами.
  * size - Размер выделяемой памяти для malloc.
  * fileName - Имя файла в котором был импользован malloc.
  * line - Строка в файле, где используется malloc. */
void* _mallocDebug(size_t size, char* fileName, size_t line);

/** Функция перехватывающая стандартный free для слежки за выделенными объектами.
 * pointer - Указатель на память, которую нужно освободить.
 * fileName - Имя файла в котором был использован free.
 * line - Строка в файла, где используется free. */
void _freeDebug(void* pointer, char* fileName, size_t line);

#define malloc(size) _mallocDebug(size, __FILE__, __LINE__)

#define free(pointer) _freeDebug(pointer, __FILE__, __LINE__)

#endif

/** Выводит объекты, которые не были освобождены до этого момента.
 * Если DEBUG_HEAP == 0, будет выведено сообщение о том, что слежка отключена. */
void _dumpMemoryLeaks();

/** Очищает список для слежки за выделенной памятью. */
void _freeHeapList();
