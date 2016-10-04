#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int next_perm(int *a, int perm_length)
{
	int i, j, k, temp, tmp;

	//Шаг 1: найти такой наибольший j, для которого A[j] < A[j+1]
	for (k = perm_length - 2; (k >= 0) && (a[k] >= a[k + 1]); k--)
		;

	//Шаг 2: увеличить A[j]. Для этого надо найти наибольшее l, для которого A[l] > A[j]. Затем поменять местами A[j] и A[l].
	if (k == -1)
		return 0;

	for (temp = perm_length - 1; a[k] >= a[temp]; temp--);

	tmp = a[k], a[k] = a[temp], a[temp] = tmp;

	//Шаг 3: записать последовательность A[j+1:perm_length] в обратном порядке.
	for (i = k + 1, j = perm_length - 1; i<j; i++, j--)
		tmp = a[i], a[i] = a[j], a[j] = tmp;
	

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
		//Перестановки состоят только из цифр, без повторений
		if ((temp < 0) || (temp > 9) || (count[temp] != 0)) {
			printf("bad input");
			return 0;
		}

		perm[perm_length] = temp;
		
		++count[temp];
		++perm_length;
	}

	scanf("%d", &N);
	
	//Выводим N перестановок, пока таковые имеются
	while ( (next_perm(perm, perm_length) && (N > 0)) ) {
		
		for (i = 0; i < perm_length; ++i)
			printf((i < perm_length - 1 ? "%d" : "%d\n"), perm[i]);
		
		--N;
	}
	
		
	return 0;
}