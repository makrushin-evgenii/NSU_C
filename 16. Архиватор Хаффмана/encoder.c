// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "bitstream.h"
#include "coding_tree.h"
#include "encoder.h"

#define ASCII_MAX_CHAR 256
#define INPUT_BUFF_SIZE 1024


//
// построение кодов Хаффмана
//

// tree - корень кодирующего дерева
// s - буферная строка
// len - позиция в строке s 
// huffman_codes массив, куда будут записаны коды символов
void build_huffman_codes(node_t* tree, uint8_t* huffman_codes[], uint8_t* s, int len) 
{
	if (!tree)
		return;

	if (tree->is_leaf) 
	{
		s[len] = 0;
		huffman_codes[tree->value] = (uint8_t*)malloc(sizeof(uint8_t) * (len + 1));
		strcpy((char*)huffman_codes[tree->value], (char*)s);
		return;
	}

	s[len] = '0', build_huffman_codes(tree->left, huffman_codes, s, len + 1);	// при спуске влево код дополняется нулем
	s[len] = '1', build_huffman_codes(tree->right, huffman_codes, s, len + 1);	// при спуске вправо код дополняется единицей
}

//
// Представление кодирующего дерева
//

// tree - корень кодирующего дерева
// tree_view - строка, принимающая представление в формате: 
// 1, если левый потомок - внутренний узел
// 0, если левый потомок - терминальный узел
// после 0 идет 8 бит ASCII кода символа
// если после ASCII кода встречен второй 0, значит
// правый потомок - тоже терминальный узел, иначе - внутренний
void build_tree_view(node_t* tree, uint8_t* tree_view, size_t* pos) 
{
	if (!tree)
		return;

	if (tree->left)		// потомок - внутренний узел
	{ 
		if (tree->left->is_leaf) 
		{
			tree_view[(*pos)++] = '0';
			tree_view[(*pos)++] = tree->left->value;
		}
		else		// потомок - терминальный узел
		{ 
			tree_view[(*pos)++] = '1';
			build_tree_view(tree->left, tree_view, pos);
		}
	}

	if (tree->right) 
	{
		if (tree->right->is_leaf) 
		{
			tree_view[(*pos)++] = '0';
			tree_view[(*pos)++] = tree->right->value;
		}
		else 
		{
			tree_view[(*pos)++] = '1';
			build_tree_view(tree->right, tree_view, pos);
		}
	}
}

// Частота вхождения каждого ASCII символа в файл. (необходимо для построения дерева)
size_t fgetc_freq(const char* input_file_name, size_t chars_freq[]) 
{
	FILE* fin = fopen(input_file_name, "r");
	if (!fin) 
	{
		printf("Cannot open input file: \"%s\"", input_file_name);
		exit(EXIT_FAILURE);
	}

	_setmode(_fileno(fin), _O_BINARY);

	uint8_t buff[INPUT_BUFF_SIZE];
	size_t buffSize = INPUT_BUFF_SIZE;
	size_t currSize = 0;
	size_t totalLen = 0;

	while ((currSize = fread(buff, 1, buffSize, fin)) > 0) 
	{
		totalLen += currSize;
		for (size_t i = 0; i < currSize; ++i)
			chars_freq[buff[i]]++;
	}

	fclose(fin);


	return totalLen;
}

// Записывает представление дерева Хаффмана tree_view в поток stream.
void bitstream_put_tree_view(bitstream* stream, uint8_t* tree_view, size_t bitsViewLen) 
{
	bool isLastEnd = false;
	for (register size_t i = 0; i < bitsViewLen; ++i) 
	{
		uint8_t currChar = tree_view[i];
		if (isLastEnd) 
		{			// в прошлой итерации был считан терминирующий символ
			bitstream_put_char(stream, currChar);
			isLastEnd = false;
		}
		else if (currChar == '0') 
		{
			bitstream_put_bit(stream, false);
			isLastEnd = true;		// следующий символ поместить в узел дерева
		}
		else if (currChar == '1')
			bitstream_put_bit(stream, true);
	}
}

// Процесс кодирования файла.
void fileCodingProcess (const char* input_file_name, const char* output_file_name, 
			uint8_t* huffman_codes[], uint8_t* tree_view, size_t total_len, size_t tree_view_len) 
{
	FILE* fin = fopen(input_file_name, "r");
	FILE* fout = fopen(output_file_name, "w");
	if (!fin) 
	{
		printf("Cannot open input file: \"%s\"", input_file_name);
		exit(EXIT_FAILURE);
	}
	if (!fout) 
	{
		printf("Cannot open output file: \"%s\"", output_file_name);
		exit(EXIT_FAILURE);
	}

	_setmode(_fileno(fin), _O_BINARY);
	_setmode(_fileno(fout), _O_BINARY);

	uint8_t buff[INPUT_BUFF_SIZE];
	size_t currSize = 0;

	bitstream bs;
	bitstream_init(&bs, fout);

	bitstream_put_nbits(&bs, (uint32_t)total_len, 32);		// кол-во символов, которые нужно декодировать
	bitstream_put_tree_view(&bs, tree_view, tree_view_len);		// представление декодирующего дерева

	// Вывод файла
	while ((currSize = fread(buff, 1, INPUT_BUFF_SIZE, fin)) > 0)
		for (register size_t i = 0; i < currSize; i++) 
		{
			uint8_t* encodedChar = huffman_codes[buff[i]];
			bitstream_put_binstr(&bs, encodedChar);
		}

	bitstream_dump(&bs);
	fclose(fin);
	fclose(fout);
}

void encode(const char* input_file_name, const char* output_file_name) 
{
	size_t chars_freq[ASCII_MAX_CHAR] = { 0 };			// частота вхождения каждого символа в файл
	size_t total_len = fgetc_freq(input_file_name, chars_freq);
	node_t * coding_tree = tree_build_with_freqs(chars_freq);	// корень кодидующего дерева
	uint8_t tree_view[4096] = { 0 };				// запись кодирующего дерева
	uint8_t* huffman_codes[ASCII_MAX_CHAR] = { 0 };			// таблица с кодами Хаффмана
	uint8_t s[32] = { 0 };
	size_t tree_view_len = 0;

	build_huffman_codes(coding_tree, huffman_codes, s, 0);
	build_tree_view(coding_tree, tree_view, &tree_view_len);

	fileCodingProcess(input_file_name, output_file_name, huffman_codes, tree_view, total_len, tree_view_len);
	
	for(size_t i = 0; i < ASCII_MAX_CHAR; ++i)
		free(huffman_codes[i]);
}
