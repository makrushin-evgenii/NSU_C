/*Задание 10. Системы счисления - 1*/ 
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜ 
#include <stdio.h>
#include <math.h>
#include <string.h>

int char_to_dig(char c){
	// '1' = 1, '2' = 2 ... 'A' = 10, 'B' = 11...
	return (c >= 'A' && c <= 'Z') ? (10 + c - 'A') : (c - '0');
}

char dig_to_char(int n){
	// 1 = '1', 2 = '2' ... 'A' = 10, 'B' = 11...
	return (n >= 0 && n <= 9) ? ('0' + n) : ('A' - 10 + n);
}

/*
 * ПЕРЕВОД в 10 СС из A СС
 * num_sys - исходная СС, number - строка содержащая запись числа в a CC
 */ 
double num_sys_to_dec(int num_sys, char *number){ 
	double sum = 0;
	int integer_part = 0;
	int i = 0; 
	char c = 0;
	//сначала читаю часть числа до запятой
	for (i = 0; (c = *number) != '.' ; ++i){
		integer_part = (integer_part * num_sys) + char_to_dig(c);
		++number;
	}
	//пропускаем точку
	++number;
	//считаю сумму разрядов до запятой
	for (i = 0; integer_part > 0; ++i){
		sum += (integer_part % num_sys) * pow(num_sys, i);
		integer_part /= num_sys;
	}
	//читаю разряды после запятой и сразу считаю их сумму
	for (i = -1; (c = *number) != '\0' ; --i){
		sum += char_to_dig(c) * pow(num_sys, i);
		++number;
	}

	return sum;
}

/*
 * ПЕРЕВОД в A СС из 10 СС
 * number - число в 10 СС, num_sys - СС в которую надо перевести
 */ 
void dec_to_num_sys(double number, int num_sys){ 
	int i = 0, j = 0;
	char c = 0;
	char integer_result_str [80], fractional_result_str[80];
	int integer_part = (int) number;
	double fractional_part = number - (int) number;
	//подсчет целой части
	do{
		integer_result_str[i++] = dig_to_char(integer_part % num_sys);
		integer_part /= num_sys;
	}while(integer_part);
	integer_result_str[i] = '\0';
	//разворот строки
	int len = i;
	for (i = 0; i < len / 2; ++i){
		int temp = integer_result_str[i];
		integer_result_str[i] = integer_result_str[len - i - 1];
		integer_result_str[len - i - 1] = temp;
	}
	// подсчет дробной части
	i = 0;
	while( fractional_part > 0 && i < 6){
		fractional_part *= num_sys;
		integer_part = (int) fractional_part;
		fractional_part -= (int) fractional_part;
		fractional_result_str[i++] = dig_to_char(integer_part);
		++i;
	}
	fractional_result_str[i] = '\0';

	printf("%s.%s\n", integer_result_str, fractional_result_str);
}

int main(){

	int num_sys1 = 10;
	int num_sys2 = 2;
	char number[]= "100.1000";

	double dec = num_sys_to_dec(num_sys1, number);
	printf("%f\n", dec);
	dec_to_num_sys(dec, num_sys2);

	return 0;
}