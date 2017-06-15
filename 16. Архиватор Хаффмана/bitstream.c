// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#include <string.h>

#include "bitstream.h"


void bitstream_init(bitstream * bitstream, FILE * stream)
{
	bitstream->_stream = stream;
	bitstream->_buffer = 0;
	bitstream->_buffer_remain = 0;
}

void bitstream_put_nbits(bitstream * bitstream, uint32_t output, size_t count)
{
	if (!count)
		return;

	count = count > 32 ? 32 : count;

	for (register size_t i = 0; i < count; i++)
	{
		bitstream->_buffer <<= 1;
		bitstream->_buffer |= (output & (1 << (count - i - 1))) != 0;

		if (++bitstream->_buffer_remain == BUFF_SIZE)	// Буфер закончился
		{ 
			fwrite(&bitstream->_buffer, 1, 1, bitstream->_stream);
			bitstream->_buffer_remain = 0;
			bitstream->_buffer = 0;
		}
	}
}

void bitstream_put_bit(bitstream * bitstream, bool bit)
{
	bitstream_put_nbits(bitstream, bit, 1);
}

void bitstream_put_char(bitstream * bitstream, uint8_t ch)
{
	bitstream_put_nbits(bitstream, ch, 8);
}

void bitstream_put_binstr(bitstream * bitstream, uint8_t * str)
{
	size_t len = strlen((const char*)str);
	for (register size_t i = 0; i < len; i++)
		bitstream_put_bit(bitstream, (str[i] == '0' ? 0 : 1));
}

bool bitstream_get_bit(bitstream * bitstream, bool * bit)
{
	uint32_t buff;
	bool result = bitstream_get_nbits(bitstream, &buff, 1);
	*bit = buff % 2;


	return result;
}

bool bitstream_get_byte(bitstream * bitstream, uint8_t * ch)
{
	uint32_t buff;
	bool result = bitstream_get_nbits(bitstream, &buff, 8);
	*ch = buff & 255;


	return result;
}

bool bitstream_get_nbits(bitstream * bitstream, uint32_t * input, size_t count)
{
	if (count > 32)
		return false;

	for (register size_t i = 0; i < count; i++)
	{
		if (!bitstream->_buffer_remain)	// Досчитываем байт в буфер, если он закончился
		{ 
			if (!fread(&bitstream->_buffer, 1, 1, bitstream->_stream))
				return false;
			bitstream->_buffer_remain = 8;
		}

		bitstream->_buffer_remain--;
		(*input) <<= 1;
		(*input) |= (bitstream->_buffer & (1 << bitstream->_buffer_remain)) != 0;
	}


	return true;
}

void bitstream_dump(bitstream* bitstream)
{
	if (bitstream->_buffer_remain)	// Остались не сброшенные биты
	{ 
		bitstream->_buffer <<= BUFF_SIZE - bitstream->_buffer_remain;
		fwrite(&bitstream->_buffer, 1, 1, bitstream->_stream);
	}
}
