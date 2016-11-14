#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/** Обозначает границу стека */
#define END 0

/** Операции, доступные на стеке */
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'

/** Операция или число(для поля is_operation) */
#define OPERATION true
#define NUMBER false

#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'

#define INPUT_SIZE 1024
#define MAX_STACK_SIZE 1024
#define MAX_OPERATION_STACK_SIZE 1024

/** Последние считанные лексемы */
enum last_item {
	LAST_START_FILE,
	LAST_NUMBER,
	LAST_OPERATION,
	LAST_OPEN_BRACKET,
	LAST_CLOSE_BRACKET
};

/** Элемент стека */
struct Item {

	// Значение данного элемента стека
	int value;

	// Если true, то в поле value хранится значение соответсвующее операции, иначе там число
	bool is_operation;
};

bool is_operator(char c) {
	return c == ADD || c == SUB || c == MUL || c == DIV;
}

bool is_number(char c) {
	return c - '0' >= 0 && c - '0' <= 9;
}

int get_operation_priority(char operation) {
	switch (operation) {
	case MUL:
	case DIV:
		return 1;
	case ADD:
	case SUB:
		return 0;
	}
	return -1;
}


/* Сообщение об ошибке */
#define AHTUNG {printf("syntax error\n"); return NULL;}
#define ALARM {printf("division by zero\n"); return;}

/** Считывает со входного потока, формирует стек и возвращает его.
* Если при формировании происходит ошибка, кричит AHTUNG и завершает работу.
*/
struct Item* infix2postfix_notation() {
	struct Item *stack = malloc(MAX_STACK_SIZE * sizeof(struct Item));

	// Стек операций
	char operators_stack[MAX_OPERATION_STACK_SIZE];

	// Считываем входную строку.
	char input[INPUT_SIZE];
	gets(input);

	size_t stack_pos = 0;
	size_t operators_stack_len = 0;

	// Тип последнего обработаного элемента (определены как #define LAST_*)
	enum last_item last_item_type = LAST_START_FILE;

	size_t pos = 0;
	while (input[pos] != '\0') {
		if (is_number(input[pos])) { // Считывание числа
			if (last_item_type == LAST_NUMBER || last_item_type == LAST_CLOSE_BRACKET) // Нет оператором м-ду числами: x y .. или .. ) x ..
				AHTUNG
				int number = 0;
			while (is_number(input[pos])) {
				number = number * 10 + (input[pos] - '0');
				pos++;
			}
			pos--;
			struct Item item = { number, NUMBER };
			stack[stack_pos++] = item;

			last_item_type = LAST_NUMBER;
		}
		else if (input[pos] == OPEN_BRACKET) { // Начало выражения в скобках
			if (last_item_type == LAST_NUMBER) // Нет оператора после числа: .. x ( ..
				AHTUNG
				operators_stack[operators_stack_len++] = input[pos];
			last_item_type = LAST_OPEN_BRACKET;
		}
		else if (is_operator(input[pos])) { // Оператор +, -, *, /
			if (last_item_type == LAST_START_FILE || last_item_type == LAST_OPEN_BRACKET) {
				if (input[pos] == ADD || input[pos] == SUB) { // Корректная обработка отрицательных чисел: - x .. и .. (- x ..
					struct Item item = { 0, NUMBER };
					stack[stack_pos++] = item;
				}
				else // Нет левого аргумента: * x .. и .. ( * x ..
					AHTUNG
			}
			if (last_item_type == LAST_OPERATION) // Два оператора подряд: .. + * ..
				AHTUNG

				// Проверяем приоритеты операций
				if (get_operation_priority(input[pos]) <= get_operation_priority(operators_stack[operators_stack_len - 1])) {
					struct Item item = { operators_stack[operators_stack_len - 1], OPERATION };
					stack[stack_pos++] = item;
					operators_stack_len--;
				}
			operators_stack[operators_stack_len++] = input[pos];
			last_item_type = LAST_OPERATION;
		}
		else if (input[pos] == CLOSE_BRACKET) { // Конец выражения в скобках
			if (last_item_type == LAST_OPEN_BRACKET) // Пустая скобка: .. ( ) .. 
				AHTUNG
				if (last_item_type == LAST_OPERATION) // Нет правого аргумента: .. ( x + ) ..
					AHTUNG
					bool found = false;
			while (operators_stack_len > 0) {
				if (operators_stack[operators_stack_len - 1] == OPEN_BRACKET) {
					found = true;
					break;
				}
				struct Item item = { operators_stack[operators_stack_len - 1], OPERATION };
				stack[stack_pos++] = item;
				operators_stack_len--;
			}
			if (!found) // До конца стека операций не было найдено открывающихся скобок, значит это ошибка
				AHTUNG
				operators_stack_len--;
			last_item_type = LAST_CLOSE_BRACKET;
		}
		else if (input[pos] == ' ') { // Пропускаем пробелы

		}
		else // Неизвестный символ
			AHTUNG
			pos++;
	}

	if (last_item_type == LAST_OPERATION) // Нет правого аргумента: "... 1 * "
		AHTUNG

		// В конце считывания закидываем все операции, оставшиеся на стеке операций, в основной стек
		while (operators_stack_len > 0) {
			if (operators_stack[operators_stack_len - 1] == OPEN_BRACKET)
				AHTUNG
				struct Item item = { operators_stack[operators_stack_len - 1], OPERATION };
			stack[stack_pos++] = item;
			operators_stack_len--;
		}

	// Помечаем конец стека
	struct Item item = { END, OPERATION };
	stack[stack_pos] = item;

	return stack;
}

/** Определяет размер стека*/
size_t stack_size(struct Item *stack) {
	size_t i = 0;
	while (!stack[i].is_operation || stack[i].value) {
		i++;
	}

	return i;
}

/** Вычисляет результат выражения*/
void postfix_calc (struct Item *stack) {
	size_t size = stack_size(stack);

	struct Item calculation[22];
	size_t calculation_pos = 0;
	int a, b, result;

	for (size_t i = 0; i < size; i++) {
		if (!stack[i].is_operation) {
			calculation[calculation_pos++].value = stack[i].value;
		}
		else {
			b = calculation[--calculation_pos].value;
			a = calculation[--calculation_pos].value;

			switch (stack[i].value) {
			case ADD:
				calculation[calculation_pos++].value = a + b;
				break;
			case SUB:
				calculation[calculation_pos++].value = a - b;
				break;
			case MUL:
				calculation[calculation_pos++].value = a * b;
				break;
			case DIV:
				if (b == 0)
					ALARM
					calculation[calculation_pos++].value = a / b;
				break;
			}
		}
	}

	result = calculation[0].value;

	printf("%d\n", result);
}


int main() {
	//freopen("input.txt", "r", stdin);

	struct Item *stack = infix2postfix_notation();

	if ((stack != NULL) && !(stack[0].is_operation && stack[0].value == 0)) {
		postfix_calc (stack);
	}

	if ((stack != NULL) && (stack[0].is_operation && stack[0].value == 0))
		printf("syntax error\n");

	free(stack);

	
	return 0;
}
