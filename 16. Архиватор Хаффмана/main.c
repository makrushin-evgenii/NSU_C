// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "leaks_debug.h"
#include "decoder.h"
#include "encoder.h"


int main(const int argc, const char** argv) 
{
	char * usage = "usage: huffman <-cd> <path1> <path2>\n";

	if (argc == 1)			// Проверка тестировщиком
	{	
		char buff[1024];
		const size_t buff_size = 1024;
		size_t cur_size = 0;

		FILE * fin = fopen("in.txt", "r");
		FILE * temp = fopen("temp", "w");

		_setmode(_fileno(fin), _O_BINARY);
		_setmode(_fileno(temp), _O_BINARY);

		fread(buff, 1, 3, fin);	// MODE + LF + CR = 3 символа
		char mode = buff[0];
		while ((cur_size = fread(buff, 1, buff_size, fin)) > 0)
			fwrite(buff, cur_size, 1, temp);

		fclose(fin);
		fclose(temp);

		if (mode == 'c')
			encode("temp", "out.txt");
		if (mode == 'd')
			decode("temp", "out.txt");
	}
	else if (argc == 4)		// Использование из консоли
	{
		if (!strcmp("-c", argv[1]))
			encode(argv[2], argv[3]);
		else if (!strcmp("-d", argv[1]))
			decode(argv[2], argv[3]);
		else 
			puts(usage);
	}
	else 
	{
		puts(usage);
	}

	return EXIT_SUCCESS;
}
