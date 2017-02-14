#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include "avltree.h"

int main()
{
	struct avltree_node *tree = NULL;

	int n = 0;
	int cur = 0;

	scanf("%d", &n);

	while (n--)
	{
		scanf("%d", &cur);
		tree = avltree_insert(tree, cur);
	}

	printf("%d\n", avltree_height(tree));

	free(tree);

	return 0;
}
