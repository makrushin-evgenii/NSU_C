/*Задание 9. Палиндром (только латиница)*/ 
/*Для теста: Go hang a salami, I'm a lasagna hog - палиндром */ 
#include <stdio.h>

int lower(char c){
	if (c >= 'A' && c <= 'Z')
		return 'a' + (c - 'A');
	return c;
}
// при чтении строки пропускаются все знаки препинания и пустые знаки
int getline(char s[]){
	int c, i;
	int pass = 0;
	for (i = 0; (i < 254) && ((c = getchar()) != EOF) && (c != '\n'); ++i )
		if ((c == '.') || (c == ',') || c == ' ' || c == '\'')
			++pass;
		else
			s[i - pass] = lower(c);
	s[i - pass] = '\0';

	return i - pass;
}

int ispal(char s[], int len){
	for (int i = 0; i < len - 1; ++i){
		if (s[i] != s[len - 1 - i])
			return 0;
	}
	return 1;
}

int main(){
	char s[255];
	int len = getline(s);

	if (ispal(s, len))
		printf("палиндром\n");
	else
		printf("не палиндром\n");
	
	return 0;
}