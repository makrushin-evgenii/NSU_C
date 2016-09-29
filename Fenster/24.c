/*Задание 24. Алгоритм Дейкстры*/ 
//(*'ー')ﾉ"･*:.｡. .｡.:*･゜ﾟ･*☆
#include <stdio.h>
#define N 10
#define INF 9999

int from, to, weight;
int a[N][N]; 
int used[N], d[N], p[N];
/*а - матрица смежности, used - пройденые вершины, 
d - расстояние от начальной вершины, p - предки вершин*/ 

void  initialize_single_source(int s){
	for (int v = 0; v < N; ++v)
	{
		used[v] = 0;
		d[v] = INF;
		p[v] = -1;
	}
	d[s] = 0;
}

void relax(int u, int v){
	if(d[v] > d[u] + a[u][v]){ //пытаемся улучшить найденый к этому моменту кратчайший путь к вершине v
		d[v] = d[u] + a[u][v];
		p[v] = u;
	}
}

int extract_min(void){
	int temp = INF, temp_i = -1;
	for (int i = 0; i < N; ++i)
		if(!used[i] && d[i] < temp){
			temp = d[i];
			temp_i = i;
		}

	return temp_i;
}

int main(void){
	// заполнение матрицы
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			a[i][j] = INF; 

	while(scanf("%d %d %d", &from, &to, &weight) == 3){
		a[from][to] = weight;
		a[to][from] = weight;
	}

	int source = 1; //исходная вершина

	// Dijkstra
	initialize_single_source(source);
	int u; //u - неиспользованая вершина с минимальным известным расстоянием
	while((u = extract_min()) != -1){
		used[u] = 1; //помечаем вершину как использованую
		for (int v = 0; v < N; ++v) //перебор всех рёбер от вершины u
			relax(u, v); //ослабление ребра
	}

	// вывод длины кратчайшего пути и вершин, через которые этот путь проходит
	for (int i = 0; i < N; ++i){
		if(d[i] == INF)
			continue; //пропускаем недосягаемые вершины
		printf("вершина %d: длина пути %d, путь проходит через вершины ", i, d[i]);
		int temp = i;
		while(p[temp] != -1){
			printf("%d ", p[temp]);
			temp = p[temp];
		}
		printf("\n");
	}
	
	return 0;
}
