// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>

int char_to_dig(char c) {
	// '1' = 1, '2' = 2 ... 'A' = 10, 'B' = 11...
	if (c >= 'a' && c <= 'z')
		c += 'A' - 'a';

	return (c >= 'A' && c <= 'Z') ? (10 + c - 'A') : (c - '0');
}

char dig_to_char(int n) {
	// 1 = '1', 2 = '2' ... 'A' = 10, 'B' = 11...
	return (n >= 0 && n <= 9) ? ('0' + n) : ('A' - 10 + n);
}

/*
* ПЕРЕВОД в 10 СС из A СС
* num_sys - исходная СС, number - строка содержащая запись числа в a CC
*/
long double num_sys_to_dec(int num_sys, char *number) {

	long double sum = 0;
	long long int integer_part = 0;
	int i = 0;
	char c = 0;

	//сначала читаю часть числа до запятой
	for (i = 0; (c = *number) != '.'; ++i) {
		integer_part = (integer_part * num_sys) + char_to_dig(c);
		++number;
	}

	//пропускаем точку
	++number;

	//считаю сумму разрядов до запятой
	for (i = 0; integer_part > 0; ++i) {
		sum += (integer_part % num_sys) * pow(num_sys, i);
		integer_part /= num_sys;
	}

	//читаю разряды после запятой и сразу считаю их сумму
	for (i = -1; (c = *number) != '\0'; --i) {
		sum += char_to_dig(c) * pow(num_sys, i);
		++number;
	}
	return sum;
}

double num_sys_to_integer_dec(int num_sys, char *number) {
	long double sum = 0;
	long long int integer_part = 0;
	int i = 0;
	char c = 0;
	//сначала читаю часть числа до запятой
	for (i = 0; (c = *number) != '\0'; ++i) {
		integer_part = (integer_part * num_sys) + char_to_dig(c);
		++number;
	}
	//считаю сумму разрядов до запятой
	for (i = 0; integer_part > 0; ++i) {
		sum += (integer_part % num_sys) * pow(num_sys, i);
		integer_part /= num_sys;
	}
	return sum;
}

/*
* ПЕРЕВОД в A СС из 10 СС
* number - число в 10 СС, num_sys - СС в которую надо перевести
*/
void dec_to_num_sys(long double number, int num_sys) {
	int i = 0, j = 0;
	char c = 0;
	char integer_result_str[80], fractional_result_str[80];
	long long int integer_part = (long long int)number;
	long double fractional_part = number - (long long int)number;

	//подсчет целой части
	do {
		integer_result_str[i++] = dig_to_char(integer_part % num_sys);
		integer_part /= num_sys;
	} while (integer_part);
	integer_result_str[i] = '\0';
	//разворот строки
	int len = i;
	for (i = 0; i < len / 2; ++i) {
		int temp = integer_result_str[i];
		integer_result_str[i] = integer_result_str[len - i - 1];
		integer_result_str[len - i - 1] = temp;
	}

	// подсчет дробной части
	i = 0;
	while (fractional_part > 0 && i < 12) {
		fractional_part *= num_sys;
		integer_part = (long long int)fractional_part;
		fractional_part -= (long long int)fractional_part;
		fractional_result_str[i++] = dig_to_char(integer_part);
	}
	//while (i < 1){
	//	fractional_result_str[i++] = '0';
	//}

	fractional_result_str[i] = '\0';

	if (i == 0)
		printf("%s.0\n", integer_result_str);
	else
		printf("%s.%s\n", integer_result_str, fractional_result_str);
}

int main() {

	int num_sys1 = 0;
	int num_sys2 = 0;
	char number[80];
	long double dec = 0;
	int fractional_part = 0;

	//freopen("in.txt", "r", stdin);
	scanf("%d %d\n", &num_sys1, &num_sys2);
	gets(number);

	/*ПРОВЕРКА ВВОДА*/
	// Если b1 и b2 в первой строке не от 2 до 16, то "bad input".
	if ((num_sys1 < 2 || num_sys1 > 16) || (num_sys2 < 2 || num_sys2 > 16)) {
		printf("bad input\n");
		return 0;
	}

	char *p = number;
	//точка - плохое начало
	if (*p == '.') {
		printf("bad input\n");
		return 0;
	}
	while (*p) {
		// Если в второй строке не b1-ричная запись, то "bad input".
		if ((char_to_dig(*p) > num_sys1 - 1) && (*p != '.')) {
			printf("bad input\n");
			return 0;
		}
		//ВОЗМОЖНО разделенных точкой на целую и дробную часть
		if (*p == '.') {
			fractional_part += 1;
		}
		++p;
	}
	//почему-то в конце её тоже не должно быть
	--p;
	if (*p == '.') {
		printf("bad input\n");
		return 0;
	}
	//больше одной запятой нам не нужно
	if (fractional_part > 1) {
		printf("bad input\n");
		return 0;
	}

	/*ПЕРЕВОД*/
	if (fractional_part)
		dec = num_sys_to_dec(num_sys1, number);
	else
		dec = num_sys_to_integer_dec(num_sys1, number);

	dec_to_num_sys(dec, num_sys2);

	return 0;
}