// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int next_perm(int *a, int perm_length) {
	int i, j, k;	
	int l;		//для запминания номера эл-та 
	int temp_digit;		// для обмена значений;

	//Шаг 1: найти такой наибольший k, для которого A[k] > A[k+1]
	k = perm_length - 1;
	while ((k >= 0) && (a[k] >= a[k + 1]))
		--k;
	
	//Шаг 2: увеличить A[k]. Для этого надо найти наибольшее l, для которого A[k] > A[l]. Затем поменять местами A[k] и A[l].
	if (k == -1)
		return 0;
	//ищу l
	l = perm_length - 1;
	while (a[k] >= a[l])
		--l;
	//меняю местами
	temp_digit = a[k]; 
	a[k] = a[l];
	a[l] = temp_digit;

	//Шаг 3: записать последовательность A[k+1:perm_length] в обратном порядке.
	for (i = k + 1, j = perm_length - 1; i < j; i++, j--){
		temp_digit = a[i];
		a[i] = a[j]; 
		a[j] = temp_digit;
	}

	return i;
}

int main(void) {
	
	int i = 0;
	char c = 0;
	int temp = 0;
	int perm[80];
	int perm_length = 0;
	int count[10] = { 0 };
	int N = 0;

	//Проверка входных данных
	while ((c = getchar()) != '\n') {
		
		temp = c - '0';
		
		if ((temp < 0) || (temp > 9) || (count[temp] != 0)) {
			printf("bad input");
			return 0;
		}

		perm[perm_length] = temp;
		
		++count[temp];
		++perm_length;
	}

	scanf("%d", &N);
	
	//Вывод перестановок
	while ( (next_perm(perm, perm_length) && (N > 0)) ) {
		
		for (i = 0; i < perm_length; ++i)
			printf((i < perm_length - 1 ? "%d" : "%d\n"), perm[i]);
		
		--N;
	}
		

	return 0;
}
