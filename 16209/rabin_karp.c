// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>



int rabin_kapr_matcer(unsigned char *Text, unsigned char *Pattern, int d, int q) {
	
	int text_length = strlen(Text);
	int pattern_length = strlen(Pattern);

	int pattern_hash = 0;
	int text_hash = 0;

	int found = 0;
	int founded_count = 0;

	int i = 0;
	int j = 0;

	//предварительная обработка
	//h(c[0],...,c[N-1]) = сумма((c[i]%3)*(3^i)):
	for (i = 0; i < pattern_length; ++i) {
		pattern_hash += (int)((Pattern[i] % 3) * pow(3, i));
		text_hash += (int)((Text[i] % 3) * pow(3, i));
	}

	//значение хэш-функции для шаблона
	printf("%d\n", pattern_hash);

	//Проверка
	for (i = 0; i <= text_length - pattern_length; ++i) {
		if (pattern_hash == text_hash) {
			found = 1;
			//проверка срезов с одинаковыми хэш-суммами на совпадение
			for (j = 0; j < pattern_length; ++j) {
				//вывод позиций всех символов в тексте, которые алгоритм сравнил с каким-либо символом из шаблона
				printf("%d ", i + 1 + j);
				//обработка ложного совпадения хэш-сумм
				if (Pattern[j] != Text[i + j]) {
					found = 0;
					break;
				}
			}

			/*
			if (found) {
				//вывод совпадающих символов
				for (s = 0; s < pattern_length; ++s) {
					printf("%d ", i + 1 + s);
				}

				++founded_count;
			}
			*/
		}
		//обновление кэш-суммы при сдвиге по тексту
		if (i < text_length - pattern_length) {
			text_hash -= (int)((Text[i] % 3));
			text_hash -= (text_hash / 3) * 2;
			text_hash += (int)((Text[i + pattern_length] % 3) * pow(3, pattern_length - 1));
		}
		
	}


	return founded_count;
}


int main() {

	setlocale(LC_ALL, "Russian");
	freopen("in.txt", "r", stdin);

	static char T[200];
	char P[80];
	int d = 1, q = 29;
	int i = 0;
	char c;


	gets(P);

	i = 0;
	while ((c = getchar()) != EOF) {
		T[i] = c;
		++i;
	}
	T[i] = '\0';


	rabin_kapr_matcer(T, P, d, q);

	return 0;
}
