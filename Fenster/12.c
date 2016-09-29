/*Задание 12. Имя пользователя*/ 
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

int startswith(char a[], char b[]){
	char temp[32];
	int i;
	for (i = 0; b[i] != ':' ; ++i)
		temp[i] = b[i];
	temp[i] = '\0';

	if (strcmp(a, temp) == 0)
		return TRUE;
	else
		return FALSE;
}

void print_username(char *s){
	char name[80];
	int count, start, j = 0;
	//пропустить 4 ':'
	for(start = 0; count <= 4 ; ++start)
		if(s[start] == ':')
			++count;
	//прочесть до первой запятой
	for (j = 0; s[start+j] != ','; ++j)
		name[j] = s[start+j];
	name[j] = '\0';
	
	printf("%s\n", name);
}

int main(int argc, char *argv[]){
	FILE *fin;
	fin = fopen("/etc/passwd", "r");

	char login[80] = "usbmux";
	char s[255];

	//поиск строки с данными о пользователе
	while(fgets(s, 255, fin))
		if (startswith(login, s) == TRUE)
			break;
	
	print_username(s);

	return 0;
}