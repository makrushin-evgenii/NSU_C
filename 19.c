/*Задание 19. Колличество вхождений слов в текст*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
	char word[80];
	int count;
	struct item *next;
};
struct item *head;

int main(void){

	FILE *fin;
	fin = fopen("input.txt", "r");

	struct item *q, *p;
	char s[80], s1[80];
	int i, j, temp;

	while(fscanf(fin, "%s", s1) == 1)
	{
		//оставить только латиницу
		for(i = 0, j = 0; s1[i] != '\0'; ++i)
			if((s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z'))
				s[j++] = s1[i];
		s[j] = '\0';

		//пройти список, проверить, нет ли такого же слова
		temp = 0;
		for(p = head; p; p = p->next)
			if(strcmp(s, p->word) == 0){
				p->count += 1;
				temp = 1;
			}
		// если нет, то добавить
		if(temp == 0){
			struct item *new_word;
			new_word = malloc(sizeof(struct item));
			strcpy(new_word->word, s);
			new_word->count = 1;
			new_word->next = head;
			head = new_word;	
		}
		
	}

	for(p = head; p; p = p->next)
		printf("%s (%d)\n", p->word, p->count);

	fclose(fin);

	return 0;
}
