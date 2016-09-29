/*Задание 3. Уравнение*/ 
#include <stdio.h>
#define eps 0.001

double f(double x){
	return (x * x - 1);
}

int main() {
	double a, b, c;
	a = 0.0;
	b = 2.0;
	while (b - a > eps){
		c = (a + b) / 2.0;
		if (f(c) < 0) 
			a = c;
		else 
			b = c; 
	}
	printf("%f\n", c );
	return 0;
}
