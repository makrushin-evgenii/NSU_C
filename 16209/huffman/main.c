// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>

#include "encoder.h"
#include "decoder.h"


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		char * input_file_name = "in.txt";		// Тестировщик всегда создает эти два файла
		char * output_file_name = "out.txt";
		// TODO: test mode
	}
	else if (argc == 4)
	{
		if (!strcmp("-c", argv[1]))
			encoding(argv[2], argv[3]);
		if (!strcmp("-d", argv[1]))
			decoding(argv[2], argv[3]);
	}
	else
	{
		puts("usage: huffman <-cd> <path1> <path2>\n");
	}
	
	return 0;
}
