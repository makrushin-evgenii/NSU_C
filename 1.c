/*Задание 1. Числа Фиббоначи*/
#include <stdio.h>

int main(){
	int n;
	int a = 0, b = 1, c;
	scanf("%d", &n);
	for(int i=1;i<=n;i=i+1){
		printf("%d ", a);
		c = a + b;
		a = b; 
		b = c;
	}

	return 0;
}