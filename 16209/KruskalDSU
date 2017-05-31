// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜
#define MAXN 5000

#include <stdio.h>
#include <stdlib.h>	// EXIT_*
#include <stdbool.h>	// bool
#include <limits.h>	// MAX_INT


typedef struct _Edge{
	int start;
	int finish;
	int length;
} Edge;

//
//	Вспомогательные функции
//

void swap(int * a, int * b){
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

// Сравнение двух ребер по длинам (для qsort)
int edge_cmp(const void * a, const void * b){
	return ( (*(Edge*)a).length - (*(Edge*)b).length );
}

// Чтение числа с проверкой границ.
//  *_limit - ожидаеммые границы значения. 
//  in      - входной файл
//  err_log - сообщения об ошибке отправляются сюда.
//  err_msg - сообщение об ошибке.
//  succes  - проверка на успешное чтение.
//  Возвращает: прочитаное число
int ranged_input(FILE* in, FILE* err_log, int low_limit, int upper_limit, char *err_msg, bool *succes)
{
	int temp = 0;

	// EOF - чтение не удалось
	if (fscanf(in, "%d", &temp) == EOF) {
		*succes = false;
		return -1;
	}

	// Прочитаное число не из заданного диапозона - сообщаем об ошибке и завершаем программу
	if ((temp < low_limit) || (upper_limit < temp))
	{
		fprintf(err_log, "%s", err_msg);
		exit(0);
	}

	*succes = true;
	return temp;
}

//
// 	Система непересекающихся множеств
//

// Используется ранговая эвристика относительно глубин деревьев
// Реализация бессовестно спизжена с http://e-maxx.ru/algo/dsu

int parent[MAXN];
int rank[MAXN];

void make_set (int v) {
	parent[v] = v;
	rank[v] = 0;
}
 
int find_set (int v) {
	if (v == parent[v])
		return v;
	return parent[v] = find_set (parent[v]);
}
 
void union_sets (int a, int b) {
	a = find_set (a);
	b = find_set (b);
	if (a != b) {
		if (rank[a] < rank[b])
			swap (&a, &b);
		parent[b] = a;
		if (rank[a] == rank[b])
			++rank[a];
	}
}


int main()
{
	FILE* in = fopen("in.txt", "r");
	FILE* out = fopen("out.txt", "w");

	if (!in || !out) return EXIT_FAILURE;
	
	bool check_input;
	int N = ranged_input(in, out, 0, MAXN, "bad number of vertices\n", &check_input);
	int M = ranged_input(in, out, 0, N*(N-1)/2, "bad number of edges\n", &check_input);

	Edge *g = (Edge *)malloc(sizeof(Edge) * M);
	for (size_t i = 0; i < M; ++i) {
		g[i].start =  ranged_input(in, out, 0, N, 	"bad vertex\n", &check_input);
		g[i].finish = ranged_input(in, out, 0, N, 	"bad vertex\n", &check_input);
		g[i].length = ranged_input(in, out, 0, INT_MAX, "bad length\n", &check_input);

		if (!check_input) {
			fprintf(out, "bad number of lines\n");
			return EXIT_FAILURE;
		}
	}

	int spanned_vertices = 1;
	// Отсортируем все рёбра по неубыванию веса
	qsort(g, M, sizeof(Edge), edge_cmp);
	//Затем поместим каждую вершину в своё дерево (т.е. своё множество)
	for (int i = 0; i < N; ++i)
		make_set(i);
	// Перебираем все рёбра (в порядке сортировки) и для каждого ребра определяем,
	// принадлежат ли его концы разным деревьям
	for (int i = 0; i < M; ++i) {
		Edge cur_egde = g[i];
		if (find_set(cur_egde.start) != find_set(cur_egde.finish)) {
			fprintf(out, "%d %d\n", cur_egde.start, cur_egde.finish);
			union_sets(cur_egde.start, cur_egde.finish);	// Объединение двух деревьев
			++spanned_vertices;
		}
	}

	// В остове не все вершины - у графа нет ни одного каркаса
	if (spanned_vertices !=  N) {
		rewind(out);
		fprintf(out, "no spanning tree\n");
	}


	return EXIT_SUCCESS;
}
