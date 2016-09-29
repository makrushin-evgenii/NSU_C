/*Задание 7. Копирование*/ 
#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *fin;
	fin = fopen(argv[1], "r");
	FILE *fout;
	fout = fopen(argv[2], "w");

	int c;
	while((c = fgetc(fin)) != EOF){
		fputc(c, fout);
	}

	return 0;
}