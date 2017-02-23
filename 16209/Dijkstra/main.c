/*Задание 24. Алгоритм Дейкстры*/
// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#define _CRT_SECURE_NO_WARNINGS 1
#define INF UINT_MAX
#define MAX_NODES 5000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// задает границы ожидаемого на ввод числа 
int ranged_input(int low_limit, int upper_limit, char *error_msg)
{
	int temp = 0;

	scanf("%d", &temp);

	if ((temp < low_limit) || (upper_limit < temp))
	{
		puts(error_msg);
		exit(0);
	}

	return temp;
}

// сравнивает расстояние до двух вершин
int dst_cmp(unsigned dist[], unsigned overflow[], unsigned node1, unsigned node2)
{
	if (overflow[node1] < overflow[node2])
		return -1;	// первая ближе
	else if (overflow[node1] > overflow[node2])
		return 1;	// первая дальше

	if (dist[node1] < dist[node2])
		return -1;
	else if (dist[node1] > dist[node2])
		return 1;

	return 0;	// равны
}

int main(void) {
	
	// для отладки
	/*if (freopen("test.txt", "r", stdin) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}*/
	
	int N = ranged_input(0, MAX_NODES, "bad number of vertices\n");
	int S = ranged_input(1, N, "bad vertex\n"); S--;	// мне удобнее считать вершины от нуля
	int F = ranged_input(1, N, "bad vertex\n");	F--;	// мне удобнее считать вершины от нуля
	int M = ranged_input(0, N * (N + 1) / 2, "bad number of edges\n");

	// граф g хранится в виде матрицы смежности: 
	// для каждой вершины v строка g[v] содержит длины рёбер, исходящих из этой вершины
	unsigned int **g = (int**)malloc(N * sizeof(unsigned int*));
	for (int i = 0; i < N; i++)
	{
		g[i] = (unsigned int*)malloc(N * sizeof(unsigned int));

		for (int j = 0; j < N; ++j)
			g[i][j] = INF;
	}

	// 5000 * (1 + 4 + 4) = 45000 Бт ~ 45 Кб
	bool used[MAX_NODES];			// пройденые вершины
	unsigned from_start[MAX_NODES];	// от начальной вершины
	unsigned overflow[MAX_NODES];	// сколько раз расстояние перешагнуло отметку в INT_MAX
	int parent[MAX_NODES];			// предки вершин

	for (int i = 0; i < N; i++)
	{ 
		used[i] = false;
		from_start[i] = (i == S) ? (0) : (INF);
		overflow[i] = 0;
		parent[i] = -1;
	}

	// заполнение матрицы смежности
	for (int i = 0; i < M; ++i)
	{
		int edge_from = ranged_input(1, N, "bad vertex\n") - 1;	// мне удобнее считать вершины от нуля
		int edge_to = ranged_input(1, N, "bad vertex\n") - 1;
		unsigned edge_len = ranged_input(0, INT_MAX, "bad length\n");

		g[edge_from][edge_to] = edge_len;
		g[edge_to][edge_from] = edge_len;
	}

	// вывод матрицы смежности 
	//{
	//	for (int i = 0; i < N; ++i)
	//	{
	//		for (int j = 0; j < N; ++j)
	//			printf("(%d)%10d", j, g[i][j]);
	//		printf("\n");
	//	}
	//}

	for (int i = 0; i < N; ++i)
	{
		// находим непосещенную вершину, минимально удаленную от старта
		int v = -1;
		for (int j = 0; j < N; ++j)
			if (!used[j] && (v == -1 || from_start[j] < from_start[v]))
				v = j;

		if (from_start[v] == INF)
			break;

		used[v] = true;

		//релаксируем все ребра, исходящие из этой вершины
		for (int j = 0; j < N; ++j)
		{
			if (g[v][j] == INF)
				continue;			// нет ребра

			int to = j;
			int len = g[v][to];

			//if (overflow[v] <= overflow[to] && from_start[v] + len < from_start[to])
			if (dst_cmp(from_start, overflow, v, to) == -1)
			{
				from_start[to] = from_start[v] + len;
				overflow[to] = overflow[v];

				while (from_start[to] > INT_MAX)
				{
					++overflow[to];
					from_start[to] -= INT_MAX;
				}

				parent[to] = v;
			}
		}
	}
	
	// расстояния от S до каждой вершины графа
	for (int i = 0; i < N; ++i)
	{ 
		if (from_start[i] == INF)
			printf("oo ");
		else if (overflow[i])
			printf("INT_MAX+ ");
		else
			printf("%d ", from_start[i]);
	}
	printf("\n");

	// вывод кратчайшего пути
	if (parent[F] == -1)
	{ 
		printf("no path\n");
	}
	/*else if (from_start[F] > INT_MAX)
	{ 
		printf("overflow\n");
	}*/
	else
	{
		for (int path_node = F; path_node != S; path_node = parent[path_node])
			printf("%d ", path_node + 1);
		printf("%d\n", S + 1);
	}



	for (int i = 0; i < N; ++i)		// ~матрица смежности
		free(g[i]);
	free(g);


	return 0;
}
