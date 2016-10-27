// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MIN_CHAR 0
#define MAX_CHAR 256

int my_memcmp(unsigned char *buf1, unsigned char *buf2, int count, int zero_point) {
	while ((*(buf1 + count) == *(buf2 + count)) && (count > 0)) {
		printf("%d ", zero_point + count);
		--count;
	}

	return count ? 0 : 1;
}

void horspool(unsigned char *source, unsigned char *needle, int source_len, int needle_len) {

	int i, j, bm_bc[MAX_CHAR];
	unsigned char ch, lastch;

	/* Preprocessing */
	for (j = 0; j < MAX_CHAR; ++j) bm_bc[j] = needle_len;
	for (j = 0; j < needle_len - 1; ++j) bm_bc[needle[j]] = needle_len - j - 1;

	/* Searching */
	lastch = needle[needle_len - 1];
	i = 0;
	while (i <= source_len - needle_len) {
		ch = source[i + needle_len - 1];

		printf("%d ", i + needle_len); // сравнение последних также необходимо вывести
		if (ch == lastch)
			my_memcmp(&source[i], needle, needle_len - 1, i); //my_memcmp сравнивает и выводит остальные, начиная с последнего

		i += bm_bc[ch];
	}
}


int main(void) {

	setlocale(LC_ALL, "Russian");
	//freopen("input.txt", "r", stdin);

	unsigned char source[256];
	unsigned char needle[256];
	char c;
	int i = 0;


	gets(needle);

	while ((c = getchar()) != EOF) {
		source[i] = c;
		++i;
	}
	source[i] = '\0';


	int needle_len = strlen(needle);
	int source_len = strlen(source);


	horspool(source, needle, source_len, needle_len);


	return 0;
}