/*Задание 16. Быстрая сортировка*/ 
#include <stdio.h>

void swap(int *i, int *j){
   int t = *i;
   *i = *j;
   *j = t;
}

int partition(int a[], int lo, int hi){
	int pivot = a[hi];
	int i = lo;
	for (int j = lo; j <= hi - 1; ++j)
		if(a[j] <= pivot){
			swap(&a[i], &a[j]);
			++i;
		}
	swap(&a[i], &a[hi]);

	return i;
}

void qs(int a[], int lo, int hi){

    if(lo < hi){
    	int p = partition(a, lo, hi);
    	qs(a, lo, p-1);
    	qs(a, p + 1, hi);
    }

}

int main(void){
	int n, a[64];
   
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

	qs(a, 0, n - 1);

	for (int t = 0; t < n; ++t)
		printf("%d ", a[t]);
	printf("\n");

	return 0;
}