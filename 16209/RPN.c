#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

int sp = 0;
float stack[1000];
float pop(void) {
	if (sp > 0) {
		return stack[--sp];
	}
	else {
		fprintf(stderr, "Невозможно выполнить POP для пустого стека.\n");
		return 0;
	}
}
void push(float a) {
	stack[sp++] = a;
}
int empty() {
	return (sp == 0);
}

int main() {
	freopen("input.txt", "r", stdin);


	int i;
	while (!feof(stdin)) {
		int c = getchar();
		float x;
		float a;
		float b;

		switch (c) {
		case '\n':
		case ' ': break;
		case '=': 
			printf("Result = %f\n", pop()); 
			return 0;
		case '+': push(pop() + pop()); break;
		case '-': push(-pop() + pop()); break;
		case '*': push(pop() * pop()); break;
		case '/': b = pop(); a = pop(); push(a / b); break;
		default:
			//вернуть символ обратно в поток входа, чтобы прочитать число
			ungetc(c, stdin);
			if (scanf("%f", &x) != 1) {
				fprintf(stderr, "\n");
				return -1;
			}
			else {
				push(x);
			}
			break;
		}
	}
	

	return 0;
}
