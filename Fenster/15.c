/*Задание 15. Простая сортировка*/
#include <stdio.h>
 
void sort(int a[], int n)
{
    int i, j, key;
 
    for(j = 1; j < n; ++j){
        key = a[j];
        for(i = j - 1; i >= 0 && a[i] > key; --i)
            a[i + 1] = a[i];
        a[i + 1] = key;
    }
}
 
int main(void) {
    int n, a[64];
   
    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
   
    sort(a, n);
    for(int i = 0; i < n; ++i)
        printf("%d ", a[i]);
       
    return 0;
}