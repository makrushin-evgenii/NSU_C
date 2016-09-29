/*Задание 6. Бинарный поиск*/ 
#include <stdio.h>

int binarysearch(int a, int mass[], int n)
{
    int left, right, middle;
    left = 0;
    right = n - 1;
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (a < mass[middle])
            right = middle - 1;
        else if (a > mass[middle])
            left = middle + 1;
        else 
            return middle;
    }
    return -1;
}

int main(){
	//воод массива
	int n;
	scanf("%d", &n);
	int a[n];
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	

	printf("%d\n", binarysearch(4, a, n));
	return 0;
}
