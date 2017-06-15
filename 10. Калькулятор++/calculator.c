// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#include "calculator.h"

bool is_operator(char c) {
	return (c == ADD) || (c == SUB) || (c == MUL) || (c == DIV) || (c == POW);
}

bool is_number(char c) {
	return c - '0' >= 0 && c - '0' <= 9;
}

size_t stack_size(struct Item *stack) {
	size_t i = 0;
	while (!stack[i].is_operation || stack[i].value) {
		++i;
	}

	return i;
}

int get_operation_priority(char operation) {
	switch (operation) {
	case POW:
		return 2;
	case MUL:
	case DIV:
		return 1;
	case ADD:
	case SUB:
		return 0;
	}
	return -1;
}

int get_operation_associativity(char operation) {
	switch (operation) {
	case POW:
		return RIGHT;
	default:
		return LEFT;
	}
	return -1;
}

struct Item* infix2postfix_notation(char *input) {
	struct Item *stack = malloc(MAX_STACK_SIZE * sizeof(struct Item));

	// Стек операций
	char operators_stack[MAX_OPERATION_STACK_SIZE];

	size_t stack_pos = 0;
	size_t operators_stack_len = 0;

	// Тип последнего обработаного элемента
	enum last_item last_item_type = LAST_START_FILE;

	size_t pos = 0;
	while (input[pos] != '\0') {
		if (is_number(input[pos])) { // Считывание числа
			if (last_item_type == LAST_NUMBER || last_item_type == LAST_CLOSE_BRACKET) // Нет оператором м-ду числами: x y .. или .. ) x ..
				SYNTAX_ERROR;
			int number = 0;
			while (is_number(input[pos])) {
				number = number * 10 + (input[pos] - '0');
				++pos;
			}
			pos--;
			struct Item item = { number, NUMBER };
			stack[stack_pos++] = item;

			last_item_type = LAST_NUMBER;
		}
		else if (input[pos] == OPEN_BRACKET) { // Начало выражения в скобках
			if (last_item_type == LAST_NUMBER) // Нет оператора после числа: .. x ( ..
				SYNTAX_ERROR;
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
					SYNTAX_ERROR;
			}
			if (last_item_type == LAST_OPERATION) // Два оператора подряд: .. + * ..
				SYNTAX_ERROR;
			// Проверяем приоритеты операций			
			// ...(если оператор o1 ассоциированный, либо лево-ассоциированный) приоритет o1 меньше либо равен приоритету оператора, находящегося на вершине стека ...
			// ...(если оператор o1 право-ассоциированный) приоритет o1 меньше приоритета оператора, находящегося на вершине стека ...
			int op_assoc = get_operation_associativity(input[pos]);		// оператор о1
			int op_prior = get_operation_priority(input[pos]);			// приоритет о1 
			int last_prior = get_operation_priority(operators_stack[operators_stack_len - 1]); // приоритет опреатора, находящегося на вершине стека
			if ((op_assoc == LEFT && op_prior <= last_prior) || (op_assoc == RIGHT && op_prior < last_prior)) {
				struct Item item = { operators_stack[operators_stack_len - 1], OPERATION };
				stack[stack_pos++] = item;
				--operators_stack_len;
			}
			operators_stack[operators_stack_len++] = input[pos];
			last_item_type = LAST_OPERATION;
		}
		else if (input[pos] == CLOSE_BRACKET) { // Конец выражения в скобках
			if (last_item_type == LAST_OPEN_BRACKET) // Пустая скобка: .. ( ) .. 
				SYNTAX_ERROR;
			if (last_item_type == LAST_OPERATION) // Нет правого аргумента: .. ( x + ) ..
				SYNTAX_ERROR;
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
				SYNTAX_ERROR;
			operators_stack_len--;
			last_item_type = LAST_CLOSE_BRACKET;
		}
		else if (input[pos] == ' ') { // Пропускаем пробелы

		}
		else // Неизвестный символ
			SYNTAX_ERROR;
		++pos;
	}

	if (last_item_type == LAST_OPERATION) // Нет правого аргумента: "... 1 * "
		SYNTAX_ERROR;

	// В конце считывания закидываем все операции, оставшиеся на стеке операций, в основной стек
	while (operators_stack_len > 0) {
		if (operators_stack[operators_stack_len - 1] == OPEN_BRACKET)
			SYNTAX_ERROR;
		struct Item item = { operators_stack[operators_stack_len - 1], OPERATION };
		stack[stack_pos++] = item;
		operators_stack_len--;
	}

	// Помечаем конец стека
	struct Item item = { END, OPERATION };
	stack[stack_pos] = item;

	return stack;
}

void postfix_calc(struct Item *stack, int *result) {

	size_t size = stack_size(stack);

	struct Item calculation[22];
	size_t calculation_pos = 0;
	int a, b;

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
					DIVISION_ERROR
					calculation[calculation_pos++].value = a / b;
				break;
			case POW:
				calculation[calculation_pos++].value = (int) pow(a, b);
				break;
			}
		}
	}

	*result = calculation[0].value;

	printf("%d\n\a", *result);
}

void rpn_solver(char *input, int *result)
{
	/* TODO: в строке input знак '$' заменить на строковый эквивалент result */
	char res_str[16];
	int2str(*result, res_str);

	char *processed_input = char_replace(input, SPEC_LR, res_str);

	/* Conversion */
	struct Item *stack = infix2postfix_notation(processed_input);

	/* Calculation */
	if ((stack != NULL) && !(stack[0].is_operation && stack[0].value == 0))
		postfix_calc(stack, result);

	if ((stack != NULL) && (stack[0].is_operation && stack[0].value == 0)) {
		free(stack);
		SYNTAX_ERROR;
	}
	
	free(stack);
}
