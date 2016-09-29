/*Задание 11. Системы счисления - 2.*/
#include <stdio.h>
#include <math.h>
#define MAXLEN 255

//возвращает максимальную степень b, меньшую n
int b_pow(double n, int b){
	if (n >= 1){
		int x = 0;
		while( pow(b, x + 1) <= n)
			++x;
		return x;
	}
	else{
		int x = 0;
		while(pow(b, x) > n)
			--x;
		return x;
	}
}

char dig(int x){
	if(x >= 10)
		return 'A' + (x - 10);
	return '0' + x;
}


int main(int argc, char const *argv[])
{
	// n - вещ число в 10сс, b - новая сс
	double n = 66.5;
	int b = 4;
	// максимальный и минимальный разряды (для вывода)
	int max_pw = b_pow(n, b); 
	int min_pw = 0;	
	// массивы под хранение целых и дробных разрядов
	int e[MAXLEN]; 
	int r[MAXLEN]; 
	for (int i = 0; i < MAXLEN; ++i)
		e[i] = r[i] = 0;
	// при вычитании из n степени b, инкрементируем счетчики
	while(n > 0){
		int temp = b_pow(n, b);
		if (temp >= 0)
			++r[temp];
		else{
			++e[-temp];
			min_pw = temp;
		}
		n -= pow(b, temp);
	}

	for (int i = max_pw; i >= 0; --i)
		printf("%c", dig(r[i]));
	printf(".");
	for (int i = 1; i <= -min_pw; ++i)
		printf("%c", dig(e[i]));
	printf("(%d)\n", b);

	return 0;
}