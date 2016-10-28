// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MIN_CHAR 0
#define MAX_CHAR 256
#define BLOCK_SIZE 1000

int my_memcmp(unsigned char *buf1, unsigned char *buf2, int count, int zero_point) {
	while ((*(buf1 + count) == *(buf2 + count)) && (count > 0)) {
		printf("%d ", zero_point + count);
		--count;
	}

	return count ? 0 : 1;
}

int main(void) {

	setlocale(LC_ALL, "Russian");
	//freopen("input.txt", "r", stdin);


	/* Input */
	unsigned char needle[32];
	char *source = (char *)malloc(BLOCK_SIZE);

	gets(needle);

	int shift = 0;
	int count_read = fread(source, 1, BLOCK_SIZE, stdin);

	int needle_len = strlen(needle);
	int source_len = strlen(source);

	int i, j, k, bm_bc[MAX_CHAR];
	unsigned char ch, lastch;


	/* Preprocessing */
	for (j = 0; j < MAX_CHAR; ++j) bm_bc[j] = needle_len;
	for (j = 0; j < needle_len - 1; ++j) bm_bc[needle[j]] = needle_len - j - 1;


	/* Searching */
	lastch = needle[needle_len - 1];
	i = 0;

	//Если считали меньше килобайта, то это последний блок
	while (count_read == BLOCK_SIZE || i <= count_read - needle_len) {

		//выход за границу - читаем новый блок
		if (i + needle_len > count_read) {
			int buf_begin = i;
			int buf_end = BLOCK_SIZE;
			int buf_len = buf_end - buf_begin;

			//перенос буфера в начало source
			for (k = 0; k < buf_len; ++k)
				source[k] = source[buf_begin + k];

			//новые данные
			count_read = fread(source + buf_len, 1, BLOCK_SIZE - buf_len, stdin) + buf_len;

			//сдвиг счетчиков
			i = 0;
			shift += BLOCK_SIZE - buf_len;
		}

		ch = source[i + needle_len - 1];

		printf("%d ", i + needle_len + shift); // сравнение последних также необходимо вывести
		if (ch == lastch)
			my_memcmp(&source[i], needle, needle_len - 1, i + shift); //my_memcmp сравнивает и выводит остальные, начиная с последнего

		i += bm_bc[ch];
	}


	return 0;
}
