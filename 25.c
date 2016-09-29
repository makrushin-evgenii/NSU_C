/*Задание 25. Полный перебор*/ 
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#include <stdio.h>
#include <math.h>
#define N 10
#define INF 9999

float x[N], y[N];
float a[N][N]; 
float min_path = 9999.9;
int i, j, temp;
/*а - матрица смежности, xy - координаты городов*/

/*ГЕНЕРАЦИЯ ПЕРЕСТАНОВОК*/
int perm[100];

void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}

void generate(int k){
	if(k == N){
		//цикл найден, найдем его длину
		float curr_path = 0;
		for (int i = 1; i < N; ++i){
			curr_path += a[perm[i - 1]][perm[i]];
		}
		curr_path += a[perm[N - 1]][perm[0]];
		if(curr_path < min_path){
			min_path = curr_path;
			//вывод пути в консоль для проверки решения
			for (int i = 1; i < N; ++i){
				printf("%d -(%f)-> %d, ", perm[i - 1], a[perm[i - 1]][perm[i]], perm[i]);
			}
			printf("%d -(%f)-> %d; (весь путь %f)\n", perm[N - 1], a[perm[N - 1]][perm[0]], perm[0], curr_path);
		}
	}
	else{
		for (int j = k; j < N; ++j)
		{
			swap(&perm[k], &perm[j]);
			generate(k + 1);
			swap(&perm[k], &perm[j]);
		}

	}
}
/*ГЕНЕРАЦИЯ ПЕРЕСТАНОВОК*/ 

int main(void){

	/*ЗАПОЛНЕНИЯ МАТРИЦЫ*/
	//чтение координат городов
	i = 0;
	while(scanf("%f %f", &x[i], &y[i]) == 2){
		++i;
	}

	// Построение матрицы смежности
	for (i = 0; i < N; ++i){
		for (j = 0; j < N; ++j){
			a[i][j] = sqrt( pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2) );
		}
	}

	//вывод матрицы смежности
	// for (i = 0; i < N; ++i){
	// 	for (j = 0; j < N; ++j){
	// 		printf("%9.6f | ", a[i][j]);
	// 	}
	// 	printf("\n");
	// }

	/*ЗАПОЛНЕНИЯ МАТРИЦЫ*/

	/*ПЕРЕБОР ВСЕХ ГАМИЛЬТОНОВЫХ ЦИКЛОВ*/	
	printf("В звеньях указаны вершины, на ребрах указана длина пути между вершинами\n");
	for (int i = 0; i < N; i++){
		perm[i] = i;
	}
	generate(0);
	/*ПЕРЕБОР ВСЕХ ГАМИЛЬТОНОВЫХ ЦИКЛОВ*/	

	/*ВЫВОД МИНИМАЛЬНОГО ПУТИ*/ 
	printf("Пройти через все %d точек можно минимум за %f ед.\n", N, min_path);
	/*ВЫВОД МИНИМАЛЬНОГО ПУТИ*/ 

	return 0;
}
