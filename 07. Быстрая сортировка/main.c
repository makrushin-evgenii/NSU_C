// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(int *i, int *j) {
	int t = *i;
	*i = *j;
	*j = t;
}

void my_qsort(int* a, int left, int right) {
	int i = left;
	int j = right;
	//в кач-ве опорного элемента выберем средний
	int x = a[(left + right) / 2];

	do {
		//слева пропускаем эл-ты меньше опорного
		while (a[i] < x) 
			i++;
		
		//справа пропускаем эл-ты больше опорного
		while (a[j] > x) 
			j--;

		//меняем местами неотсортированные эл-ты, если такие остались
		if (i <= j) {
			if (a[i] > a[j])
				swap(&a[i], &a[j]);
			i++;
			j--;
		}
	} while (i <= j);

	//рекурсивно вызываем функцию для отрезков меньших и больних значений
	if (i < right)
		my_qsort(a, i, right);
	if (left < j)
		my_qsort(a, left, j);
}


int main(void) {
	long int n;
	static int a[3000000];

	scanf("%d\n", &n);
	for (long int i = 0; i < n; ++i)
		scanf("%d", &a[i]);

	my_qsort(a, 0, n - 1);

	for (long int t = 0; t < n; ++t)
		printf("%d ", a[t]);
	printf("\n");

	return 0;
}