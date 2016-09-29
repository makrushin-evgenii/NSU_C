/*Задание 17. Пирамидальная сортировка*/ 
#include <stdio.h>

void swap(int *i, int *j){
   int t = *i;
   *i = *j;
   *j = t;
}

void shift_down(int a[], int i, int j){
	int max_child;
	while( i * 2 + 1 < j){
		if((i * 2 + 1 == j - 1) || (a[i * 2 + 1] > a[i * 2 + 2]))
			max_child = i * 2 + 1;
		else
			max_child = i * 2 + 2;
		if(a[i] < a[max_child]){
			swap(&a[i], &a[max_child]);
			i = max_child;
		}
		else
			break;
	}
}

void hsort(int a[], int n){
	for (int i = n / 2 - 1; i >= 0; --i)
		shift_down(a, i, n);
	for (int i = n - 1; i > 0; --i){
		swap(&a[0], &a[i]);
		shift_down(a, 0, i);
	}
}


int main(void){
	int n, a[64];
   
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

	hsort(a, n);

	for (int i = 0; i < n; ++i)
		printf("%d ", a[i]);

	return 0;
}