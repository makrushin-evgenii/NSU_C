//
//  leaks_debug.c
//  DataBase
//
//  Created by Кирилл on 25.03.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

#include "leaks_debug.h"

#if DEBUG_HEAP > 0

typedef struct HeapItem {
	void* next;
	void* pointer;
	char* fileName;
	size_t line;
	size_t counter;
} HeapItem;

typedef struct List {
	struct HeapItem *head;
} List;

List* heap = NULL;
size_t counter = 0;

#undef malloc
#undef free

/** Создает новый список. */
List* listNew() {
	List* list = (List*)malloc(sizeof(List));
	list->head = NULL;
	return list;
}

/** Добавляет элемент в начало спика.
 * Добавление NULL запрещено. */
void listPush(List* list, HeapItem* item) {
	if (!list || !item)
		return;
	item->next = list->head;
	list->head = item;
}

/** Удаляет элемент из начала списка и возвращает его значение.
 * Если список был пуст, возвращает NULL. */
HeapItem* listPop(List* list) {
	if (!list || !list->head)
		return NULL;

	HeapItem* item = list->head;
	list->head = list->head->next;
	return item;
}

/** Удаляет элемент на данной позиции и возвращает его значение.
 * Если на данной позиции нет элемента, возвщает NULL. */
void* listRemoveItem(List* list, size_t position) {
	if (!list || !list->head)
		return NULL;

	if (!position)
		return listPop(list);

	position--;
	HeapItem* node = list->head;
	while (node->next && position-- > 0)
		node = node->next;

	HeapItem* remove = node->next;
	if (!remove)
		return NULL;

	node->next = remove->next;

	return remove;
}

/** Для каждого элемента списка вызывает функцию compare с аргументами для сравнения.
 * Если compare возвращает true, функция возвращает позицию элемента на котором compare вернула true.
 * Если compare ни разу не вернула true, функция возвращает -1. */
int listIndexOf(List* list, const void* request, bool(compare)(const void*, const void*)) {
	if (!list || !request)
		return -1;

	HeapItem* node = list->head;
	int pos = 0;
	while (node) {
		if (compare(request, node))
			return pos;
		node = node->next;
		pos++;
	}

	return -1;
}

/** Очищает список.
 * Если freeValues - истина, применяет free к элементам списка. */
void listFree(List* list, bool freeValues) {
	if (!list)
		return;
	while (list->head) {
		void* value = listPop(list);
		if (freeValues)
			free(value);
	}
	free(list);
}

/** Функция перехватывающая стандартный malloc для слежки за выделенными объектами.
 * size - Размер выделяемой памяти для malloc.
 * fileName - Имя файла в котором был импользован malloc.
 * line - Строка в файле, где используется malloc. */
void* _mallocDebug(size_t size, char* fileName, size_t line) {
	if (!heap)
		heap = listNew();

	HeapItem* heapItem = (HeapItem*)malloc(sizeof(HeapItem));

	void* pointer = malloc(size);

	heapItem->pointer = pointer;
	heapItem->fileName = fileName;
	heapItem->line = line;
	heapItem->counter = counter++;

	listPush(heap, heapItem);

#if DEBUG_HEAP > 1
	printf("Malloc %ld:<%p> in file: \"%s\" at line %ld\n", counter - 1, pointer, fileName, line);
#endif
	return pointer;
}

/** Сравнивает две записи кучи по указателям. */
bool compareHeapItems(const void* item1, const void* item2) {
	return ((HeapItem*)item1)->pointer == ((HeapItem*)item2)->pointer;
}

/** Функция перехватывающая стандартный free для слежки за выделенными объектами.
 * pointer - Указатель на память, которую нужно освободить.
 * fileName - Имя файла в котором был использован free.
 * line - Строка в файла, где используется free. */
void _freeDebug(void* pointer, char* fileName, size_t line) {
	if (!heap)
		return;

	HeapItem patternItem;
	patternItem.pointer = pointer;

	int position = listIndexOf(heap, &patternItem, &compareHeapItems);
	if (position == -1)
		return;

	HeapItem* removed = listRemoveItem(heap, position);

	free(pointer);

#if DEBUG_HEAP > 1
	size_t counter = removed->counter;
	printf("Free %ld:<%p> in file: \"%s\" at line %ld\n", counter, pointer, fileName, line);
#endif
	free(removed);
}

#endif

/** Выводит объекты, которые не были освобождены до этого момента.
 * Если DEBUG_HEAP == 0, будет выведено сообщение о том, что слежка отключена. */
void _dumpMemoryLeaks() {
#if DEBUG_HEAP > 0
	if (!heap || !heap->head) {
		printf("==== Nothing to dump. ====\n");
		return;
	}
	HeapItem* node = heap->head;

	if (node)
		printf("==== Has locked pointers at heap. Dump: ====\n");

	while (node) {
		printf("%ld:<%p> malloc in \"%s\" at line %ld\n", node->counter, node->pointer, node->fileName, node->line);
		node = node->next;
	}
	printf("==== Dump complete. ====\n");

#else
	printf("Heap debug disabled. No output.\n");
#endif
}

/** Очищает список для слежки за выделенной памятью. */
void _freeHeapList() {
#if DEBUG_HEAP > 0
	if (heap) {
		listFree(heap, true);
		heap = NULL;
		counter = 0;
	}
#endif
}
