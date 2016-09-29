/*Задание 8. Колличество символов, слов и строк.*/ 
#include <stdio.h>
#define IN 1
#define OUT 0

int main(int argc, char *argv[]){
	FILE *fin;
	fin = fopen(argv[1], "r");

	int c, char_count, word_count, line_count, state;

	state = OUT;
	line_count = word_count = char_count = 0;
	
	while((c = fgetc(fin)) != EOF){
		++char_count;
		if(c == '\n')
			++line_count;
		if(c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if(state == OUT){
			state = IN;
			++word_count;
		}
	}

	printf("%d символа,\n", char_count);
	printf("%d слова,\n", word_count);
	printf("%d строки.\n", line_count);

	return 0;
}