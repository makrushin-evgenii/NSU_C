// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#include "util.h"


char *char_replace(char *s, char dest, char *src)
{
	int dest_idx = 0;		// индекс заменяемого символа
	int dest_count = 0;		// кол-во заменяемых символов
	int s_len = strlen(s);
	int src_len = strlen(src);

	for (int i = 0; i < s_len; ++i)
		dest_count += (s[i] == dest) ? (1) : (0);

	if (!dest_count)	// нечего заменять
		return s;

	int result_len = s_len - dest_count + (src_len * dest_count);

	char *temp = (char *)malloc(result_len + 1);	//буфер
	char *res = (char *)malloc(result_len + 1);

	strcpy(temp, s);	// инициализация буфера

	while (dest_count--)
	{
		for (dest_idx = 0; temp[dest_idx] != dest; ++dest_idx);	//индекс спецсимвола

		strncpy(res, temp, dest_idx);							// часть до спецсимвола
		strncpy(res + dest_idx, src, src_len);					// сам спецсимвол заменяется на число
		strcpy(res + dest_idx + src_len, temp + dest_idx + 1);	// часть после спецсимвола
		strcpy(temp, res);										// сохранение в буфер
	}

	free(temp);	// буфер

	return res;
}

/* 
* reverse:  переворачиваем строку s на месте
* нужно для int2str
*/
void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void int2str(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  // записываем знак 
		n = -n;          // делаем n положительным числом 
	i = 0;
	do {       //генерируем цифры в обратном порядке 
		s[i++] = n % 10 + '0';   // берем следующую цифру 
	} while ((n /= 10) > 0);     // удаляем 
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
