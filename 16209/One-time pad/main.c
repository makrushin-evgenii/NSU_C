#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
// #include <unistd.h>	// getopt() куда-то пропал
#include <string.h>		// поэтому перебрал ключи вручную

/* инкремент по модулю n */
int modular_increment(int *idx, int n)
{
	*idx = (*idx + 1) % n;
}

int main(int argc, char *argv[])
{
	char buff[1024];										// читать будем блоками по киловайту
	const size_t buff_size = sizeof(buff) / sizeof(*buff);	// но  это не точно
	size_t cur_size = 0;									// сколько смогли прочитать
	
	char *key = (argc > 1) ? (argv[1]) : ("some semi-secret key");	// секр. ключ - первый аргумент cmd
	unsigned key_len = strlen(key);	
	unsigned idx = 0;	// указывает на символ ключа, с которым будем XOR'ить

	FILE *fin = stdin;		// по умолчанимаю ввод через stdin
	FILE *fout = stdout;	// по умолчанимаю вывод через stdout

	//
	// Спросить при сдаче: какая альтернатива getopt() под Win?
	//

	if (argc > 3)	// введен один ключ -i или -o + его параметр
	{
		if (!strcmp(argv[2], "-i"))
			fin = fopen(argv[3], "r");
		else if (!strcmp(argv[2], "-o"))
			fout = fopen(argv[3], "w");
	}

	if (argc > 4)	// введен eщё один ключ -i или -o + его параметр
	{
		if (!strcmp(argv[4], "-i"))
			fin = fopen(argv[5], "r");
		else if (!strcmp(argv[4], "-o"))
			fout = fopen(argv[5], "w");
	}
	
	_setmode(_fileno(fin), _O_BINARY);
	_setmode(_fileno(fout), _O_BINARY);

	while ((cur_size = fread(buff, 1, buff_size, fin)) > 0)
	{
		for (int i = 0; i < cur_size; ++i)
		{ 
			buff[i] ^= key[idx];
			modular_increment(&idx, key_len);
		}

		fwrite(buff, cur_size, 1, fout);
	}

	return 0;
}