// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

#include "leaks_debug.h"
#include "decoder.h"
#include "bitstream.h"
#include "coding_tree.h"


// Декодирование одного символа из потока input спуском по кодирующему дереву tree
uint8_t tree_get_char(bitstream* input, node_t* tree)
{
	if (tree->is_leaf)
		return tree->value;

	bool bit;
	bitstream_get_bit(input, &bit);


	return bit ? tree_get_char(input, tree->right) : tree_get_char(input, tree->left);
}

// Рекурсивное восстановление дерева tree по его бинарному представлению в потоке input
void rebuild_tree(bitstream* input, node_t* tree)
{
	bool bit;
READ:;
	if (!bitstream_get_bit(input, &bit))
		return;
	if (bit)
	{
		if (!tree->left)
		{
			tree->left = tree_new_internal(NULL, NULL);
			rebuild_tree(input, tree->left);
			goto READ;
		}
		else
		{
			tree->right = tree_new_internal(NULL, NULL);
			rebuild_tree(input, tree->right);
		}
	}
	else
	{
		if (!tree->left)
		{
			uint8_t ch;
			if (!bitstream_get_byte(input, &ch))
			{
				printf("Wrong tree view!\n");
				exit(EXIT_FAILURE);
			}
			tree->left = tree_new_leaf(0, ch);
			goto READ;
		}
		else
		{
			uint8_t ch;
			if (!bitstream_get_byte(input, &ch))
			{
				printf("Wrong tree view!\n");
				exit(EXIT_FAILURE);
			}
			tree->right = tree_new_leaf(0, ch);
		}
	}
}

// Чтение структуры кодирующего дерева из потока input
node_t* read_tree(bitstream* input)
{
	node_t* tree = tree_new_internal(NULL, NULL);
	rebuild_tree(input, tree);


	return tree;
}

void decode(const char* input_file_name, const char* output_file_name)
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

	bitstream input;
	bitstream_init(&input, fin);
	bitstream output;
	bitstream_init(&output, fout);

	uint32_t fileLen;
	bitstream_get_nbits(&input, &fileLen, 32);	// Сколько байт было закодировано

	node_t * tree = read_tree(&input);	// Кодирующее дерево записано после длины файла

	while (fileLen-- > 0)			// Дальше закодированные данные (и пару фейк-битов в конце)
		bitstream_put_char(&output, tree_get_char(&input, tree));

	tree_free(tree);

	fclose(fin);
	fclose(fout);
}
