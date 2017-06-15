// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜    
#define _CRT_SECURE_NO_WARNINGS 1


#include <stdio.h>
#include <crtdbg.h>  
#include <assert.h>
#include "linked_list.h"


void print_int(Node *node)
{
	int *temp = node->data;
	printf("%d ", *temp);
}

void print_double(Node *node)
{
	double *temp = node->data;
	printf("%f ", *temp);
}

int node_with_double_cmp(Node *node, double *a)
{
	double *temp = node->data;
	double diff = *temp - *a;

	if (diff > 0)
		return 1;
	
	if (diff < 0)
		return -1;
	
	return 0;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/* foreach по списку обьектов типа int */
	{
		int arr[] = { 1, 2, 3, 4, 5 };
		Node *int_list = NULL;

		for (size_t i = 0; i < 5; ++i)
			list_push_back(&int_list, node_new(&arr[i]));

		list_foreach(int_list, print_int);
		list_free(&int_list);
	}
	printf("\n");

	/* foreach по списку обьектов типа double */
	{
		double arr[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		Node *double_list = NULL;

		for (size_t i = 0; i < 5; ++i)
			list_push_back(&double_list, node_new(&arr[i]));

		list_foreach(double_list, print_double);
		list_free(&double_list);
	}
	printf("\n");

	/* foreach по пустому массиву */
	{
		Node *double_list = NULL;

		list_foreach(double_list, print_double);
		list_free(&double_list);
	}
	printf("\n");

	/* поиск по списку обьектов типа double */
	{
		double arr[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		Node *double_list = NULL;

		for (size_t i = 0; i < 5; ++i)
			list_push_back(&double_list, node_new(&arr[i]));

		/* Тест list_find #1: искомый элемент есть в списке */
		{
			double correct_key = 1.1;
			assert(*(double *)list_find(double_list, node_with_double_cmp, &correct_key)->data == correct_key);
		}

		/* Тест list_find #2: искомого элемента нет в списке */
		{
			double wrong_key = 0.0;
			assert(list_find(double_list, node_with_double_cmp, &wrong_key) == NULL);
		}

		list_free(&double_list);
	}
	printf("\n");


	return 0;
}
