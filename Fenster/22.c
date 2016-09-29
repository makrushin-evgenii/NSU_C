/*Задание 22. Обход в глубину*/ 
// для проверки:
// 0 2
// 0 4
// 0 6
// 1 9
// 2 0
// 2 3
// 3 2
// 3 4
// 4 0
// 4 3
// 6 0
// 6 7
// 6 8
// 7 6
// 8 6
// 9 1
// должно вывести 0 2 3 4 6 7 8, при начальной вершине 0
#include <stdio.h>

int n, from, to;
int a[100][100];
int visited[100];

void dfs(int v){
	visited[v] = 1;
	for (int i = 0; i < n; ++i)
		if(a[v][i] && !visited[i])
			dfs(i);
}

int main(void){

	n = 10;
	//инициализация нулями
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j)
			a[i][j] = 0;
		visited[i] = 0;
	}

	// чтение ребер
	while(scanf("%d %d", &from, &to) == 2){
		a[from][to] = 1;
		a[to][from] = 1;
	}

	//обход в глубину из начальной вершины
	dfs(0);

	// вывод вершин, достижимых из начальной вершины
	for (int i = 0; i < n; ++i)
		if(visited[i])
			printf("%d ", i);

	return 0;
}
