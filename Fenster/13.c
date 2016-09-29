/*Задание 13. Разбор формата CSV*/ 
//(*'ー')ﾉ"･*:.｡. .｡.:*･゜ﾟ･*☆
#include <stdio.h>
#define OUT 0
#define IN 1
#define SEP ','

int state  = OUT;
char c, buf;

int main(void){

	printf("CSV to <table></table>, (Sepatator: %c)\n", SEP);
	printf("<table>\n");

	for (buf = '\n', c = getchar(); c != EOF; buf = c, c = getchar())
	{
		//ВЫВОД РАЗМЕТКИ
		//начало новой строки
		if((state == OUT) && (buf == '\n')){
			printf("\t<tr>\n\t\t<td>");
		}
		//разделение столбцов
		if((state == OUT) && (c == SEP)){
			printf("</td>\n\t\t<td>");
		}
		//конец строки
		if((state == OUT) && (c == '\n')){
			printf("</td>\n\t</tr>\n");
		}

		//СМЕНА СОСТОЯНИЯ
		if((state == IN) && (c == '"')){
			state = OUT;
		}
		else if((state == OUT) && (c == '"')){
			state = IN;
		}
		
		//ВЫВОД СОДЕРЖИМОГО
		//Значения, содержащие зарезервированные символы (двойная кавычка, запятая, точка с запятой, новая строка) обрамляются двойными кавычками
		//Если в значении встречаются кавычки — они представляются в файле в виде двух кавычек подряд.
		if(((c != SEP) && (c != '\n') && (c != '"')) || ((state == IN) && (c != '"')) || ((state == IN) && (c == '"') && (buf == '"'))){
			//для переноса строки в html используется одиночный тег <br>
			if(c == '\n')
				printf("<br>");
			else			
				putchar(c);
		}
	}

	//Если последняя строка заканчивается не переводом строки, то
	//обрабатываем этот случай
	if(buf != '\n')
		printf("</td>\n\t</tr>\n");

	printf("</table>\n");

	return 0;
}
