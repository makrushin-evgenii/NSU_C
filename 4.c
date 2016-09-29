/*Задание 4. Даты*/ 
#include <stdio.h>

int leap_year(int x){
	if ((x % 400 == 0) || ((x % 4 == 0) && (x % 100 != 0)))
		return 1;
	return 0;
}

int main(){
	/*кол-во дней в каждом месяце*/
	int days[12] = {31, 999, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int d1, m1, y1, d2, m2, y2;
	int count = 1; 
	
	scanf("%d/%d/%d/", &d1, &m1, &y1);
	scanf("%d/%d/%d/", &d2, &m2, &y2);
	/*проверим, не начинаем ли мы счет с високосного года*/
	if (leap_year(y1) == 1)
		days[1] = 29;
	else
		days[1] = 28;

	/*перебираем ВСЕ дни, подсчитываем итерации*/ 
	while( (d1 != d2) || (m1 != m2) || (y1 != y2) ){
		if (d1 < days[m1-1]){
			d1 = d1 + 1;
			count = count + 1;
		}
		if (d1 == days[m1-1]){
			d1 = 1;
			m1 = m1 + 1;
			count = count + 1;
		}
		if (m1 == 13){
			m1 = 1;
			y1 = y1 + 1;
			/* снова проверка на високосные года */
			if (leap_year(y1) == 1)
				days[1] = 29;
			else
				days[1] = 28;
		}
	}
	
	printf("с %02d/%02d/%d по %02d/%02d/%d прошло %d дней \n", d1, m1, y1, d2, m2, y2, count);
	return 0;
}
