/*Задание 20. Хэш-таблицы.*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
	char word[80];
	int count;
	struct item *next;
};
struct item *hash_table[80];

int hash_func(char *s){
	return strlen(s);
}

int main(void){

	struct item *q, *p;
	char s[80], s1[80];
	int i, j, cur_hash, temp;

	while(scanf("%s", s1) == 1){
		//оставить только латиницу
		for(i = 0, j = 0; s1[i] != '\0'; ++i)
			if((s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z'))
				s[j++] = s1[i];
		s[j] = '\0';

		// вычислить хэш для прочитаного слова
		cur_hash = hash_func(s);

		//пройти цепочку, проверить, нет ли уже этого слова
		temp = 0;
		for(p = hash_table[cur_hash]; p; p = p->next)
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
			new_word->next = hash_table[cur_hash];
			hash_table[cur_hash] = new_word;	
		}
	}

	//вывод всех цепочек
	for (int i = 0; i < 80; ++i)
		for(p = hash_table[i]; p; p = p->next)
			printf("%s (%d)\n", p->word, p->count);

	return 0;
}
