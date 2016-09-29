/*Задание 5. Проверка свойств элементов*/ 
#include <stdio.h>

int isprime(int x){
	if (x < 2)
		return 0;
	for (int i = 2; i < x; ++i)
		if (x % i == 0) 
			return 0;
	return 1;
}

int main(){
	//воод массива
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	//подсчет простых 
	int count = 0;
	for (int i = 0; i < n; ++i)
	{
		if (isprime(a[i]) == 1)
			count++;
	}

	if (count == n)
		printf("а) все элементы массива являются простыми числами\n");
	else
		printf("а) не все элементы массива являются простыми числами\n");

	if (count > 0)
		printf("б) среди элементов массива есть простое число\n");
	else
		printf("б) среди элементов массива нет простых чисел\n");

	return 0;
}
