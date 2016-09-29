/*Задание 2. Алгоритм Евклида*/
#include <stdio.h>

/*int gcd(int m, int n){ 
	// первый операнд должен быть больше 
	if (m < n){
		m = m ^ n;
		n = n ^ m;
		m = m ^ n;
	}
	// сам алгоритм без рекурсии
	while (m % n != 0){
		n = m % n;
		m = n;
	}
	return (n);
}*/

int gcd(int m, int n){ 
	// в рекурсивной версии менять операнды необязательно
	if (m % n == 0)
		return n;
	else
		return gcd(n, m % n);

}

int main(){
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", gcd(a, b));
	return 0;
}