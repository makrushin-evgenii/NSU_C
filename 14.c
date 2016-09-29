/*Задание 14. Перестановки.*/ 
#include <stdio.h>

int N;
int a[100];

void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}

void generate(int k){
	if(k == N){
		for (int i = 0; i < N; ++i)
			printf("%d ", a[i]);
		putchar('\n');	
	}
	else{
		for (int j = k; j < N; ++j)
		{
			swap(&a[k], &a[j]);
			generate(k + 1);
			swap(&a[k], &a[j]);
		}

	}
}


int main(void){
	N = 3;
	for (int i = 0; i < N; ++i)
		a[i] = i + 1;
	generate(0);

	return 0;
}
