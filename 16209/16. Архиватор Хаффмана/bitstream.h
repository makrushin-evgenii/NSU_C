// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define BUFF_SIZE 8

typedef struct bitstream {
	FILE *	_stream;
	uint8_t _buffer;
	size_t	_buffer_remain;
} bitstream;

// Инициализирует bitstream для работы с файлом stream.
void bitstream_init(bitstream * bitstream, FILE * stream);

// Записывает count битов из буфера output в поток bitstream (не более 32).
void bitstream_put_nbits(bitstream * bitstream, uint32_t output, size_t count);

//  Записывает бит bit в поток bitstream.
void bitstream_put_bit(bitstream * bitstream, bool bit);

// Записывает ASCII код символа ch в поток bitstream.
void bitstream_put_char(bitstream * bitstream, uint8_t ch);

// Записывает строку str в поток bitstream в бинарном виде (строка вида 010101).
void bitstream_put_binstr(bitstream * bitstream, uint8_t * str);

// Читает один бит из потока bitstream.
bool bitstream_get_bit(bitstream * bitstream, bool * bit);

// Читает один байт из потока (т.е. один ASCII символ).
bool bitstream_get_byte(bitstream * bitstream, uint8_t * ch);

// Считывает несколько count битов из потока bitstream в буфер input.
bool bitstream_get_nbits(bitstream * bitstream, uint32_t * input, size_t count);

// Выводит оставшиеся в буфере bitstream'а биты.
void bitstream_dump(bitstream * bitstream);
