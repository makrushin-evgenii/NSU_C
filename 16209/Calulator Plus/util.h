#pragma once

#define _CRT_SECURE_NO_WARNINGS 1
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#include <string.h>
#include <stdlib.h>


/*
* Меняет все вхождения символа dest в строка s на строку src
* Возращает указатель на строку с заменами
*/
char *char_replace(char *s, char dest, char *src);

/*
* int2str:  конвертируем n в символы в s
*/
void int2str(int n, char s[]);
