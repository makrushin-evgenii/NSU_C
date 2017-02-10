#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util.h"

/* Спецсимвол: результат последнего выражения*/
#define SPEC_LR '$'

/* Обозначает границу стека */
#define END 0

/* Операции, доступные на стеке */
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define POW '^'

/* Операция или число(для поля is_operation) */
#define OPERATION true
#define NUMBER false

#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'

#define INPUT_SIZE 1024
#define MAX_STACK_SIZE 1024
#define MAX_OPERATION_STACK_SIZE 1024

/* Очередность операций */
#define LEFT 0
#define RIGHT 1

/* Последние считанные лексемы */
enum last_item {
	LAST_START_FILE,
	LAST_NUMBER,
	LAST_OPERATION,
	LAST_OPEN_BRACKET,
	LAST_CLOSE_BRACKET
};

/* Элемент стека */
struct Item {

	// Значение данного элемента стека
	int value;

	// Если true, то в поле value хранится значение соответсвующее операции, иначе там число
	bool is_operation;
};

/* Сообщения об ошибке */
#define SYNTAX_ERROR {printf("syntax error\n"); return NULL;}
#define DIVISION_ERROR {printf("division by zero\n"); return;}


bool is_operator(char c);

bool is_number(char c);

/* Определяет размер стека */
size_t stack_size(struct Item *stack);

/** Считывает со входного потока, формирует стек и возвращает его.
 * Если при формировании происходит ошибка, то выдает сообщение об ошибке завершает работу.
 */
struct Item* infix2postfix_notation(char *input);

/* Вычисляет результат выражения */
void postfix_calc(struct Item *stack, int *result);

/** Вычисляет значение выражения, выводит результат в консоль.
* сохраняет значение в переменную result.
* Если при формировании происходит ошибка, то выдает сообщение об ошибке и завершает работу.
*/
void rpn_solver(char *input, int *result);
